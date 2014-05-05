from asciiworkspace import AsciiWorkspace

"""
HOW IT WORKS
============

The ascii UML layout is generated from the graph model and relies on the call
    graph.nodes_sorted_by_generalisation()
which returns the nodes in an order conducive to ascii layout.

The order of nodes returned is something like:
[('A', 'root'), ('B', 'fc'), ('D', 'tab'), ('F', 'tab'), ('C', 'fc'), ('H', 'fc'), ('E', 'root')]
or
[(m, 'root'), (s, 'root'), (f, 'root')]

Where root means start a newline and render a box.  (exception to this is where
you have multiple roots by themselves, then we spread them out across the page)

Where 'fc' means first child under a root.  Usually a subclass rendered along
the left edge of the page.

Where 'tab' means tab out to the next column in the same row.

Sometimes to avoid wiring cross-overs, we write out a class a second time as
an 'alias' which looks like this:

+-----------------------------+
|             ogl             |
+-----------------------------+
              .                                                            [ ogl ]          
             /_\                                                              .             
              |                                                              /_\            
              |                                                               |             
              |                                                               |             
+-----------------------------+                                     +----------------------+
|        UmlShapeCanvas       |                                     |     MyEvtHandler     |
|-----------------------------|                                     |----------------------|
| scrollStepX                 |  ---->  [ LayoutBasic ]             | log                  |
| scrollStepY                 |  ---->  [ OverlapRemoval ]          | frame                |


Aliases appear in [nnnnn] square brackets. Here is another example of the use of
aliases in the case of multiple inheritance:

+------+
| Mary |
+------+
                             
[ Mary ][ Sam ]       +-----+
  .                   | Sam |
 /_\                  +-----+
  |                          
  |                          
  |                          
+------+                     
| Fred |                     
+------+                     

The utility class 'asciiworkspace' is a nice class which looks after organising
things in rows and columns with appropriate padding.  You send it chunks of text
and flush/newline commands and it will appear in a nice grid format.

unit tests in
    test_graph_nodes.py
    test_asciiworkspace_01.py
    test_asciiworkspace_02.py
    
"""

class NodeWidthCalc:
    def __init__(self, node):
        self.node = node
        self.maxlen = 0
    def _scan(self, lzt):
        for line in lzt:
            if len(line) > self.maxlen:
                self.maxlen = len(line)
    def calc(self):
        self.maxlen = len(self.node.id)
        if self.node.__class__.__name__ == 'UmlNode':  # TODO need to have every node figure out its own width !!!
            self._scan(self.node.attrs)
            self._scan(self.node.meths)
        return self.maxlen

class model_to_ascii_builder:
    def __init__(self):
        self.result = ""
        self.pending_composition_line_output = []
        #self.alternating_lines = False

    def line(self, ch='-', n=30, top_bottom=False):
        CORNER = "+"
        SIDE = "|"
        if top_bottom:
            s = CORNER + ch*n + CORNER
        else:
            s = SIDE + ch*n + SIDE
        return s + "\n"

    def top_or_bottom_line(self, maxwidth):
        return self.line(n=maxwidth, top_bottom=True)

    def attrs_or_meths(self, lzt, maxwidth):
        result = self.line(n=maxwidth)
        for entry in lzt:
            result += "| %-*s |" % (maxwidth -2, entry)
            if self.pending_composition_line_output: # and self.alternating_lines:
                edge = self.pending_composition_line_output.pop()
                result += "  ---->  [ %s ]" % (edge)
            #self.alternating_lines = not self.alternating_lines
            result += "\n"
        return result

    def removeDuplicates(self, lzt):
        # workaround a bug in pynsource where duplicate edges are recorded - to be fixed.  For now remove duplicates.
        return list(set(lzt))

    def CalcRelations(self, node, graph):
        rels_composition = self.removeDuplicates([edge['source'].id for edge in graph.edges if edge['target'].id == node.id and edge.get('uml_edge_type', '') != 'generalisation'])
        #rels_composition = self.removeDuplicates([edge['source'].id for edge in graph.edges if edge['target'].id == node.id and edge.get('uml_edge_type', '') == 'composition'])
        rels_generalisation = self.removeDuplicates([edge['target'].id for edge in graph.edges if edge['source'].id == node.id and edge.get('uml_edge_type', '') == 'generalisation'])
        return rels_composition, rels_generalisation

    def EnsureRootAsWideAsChild(self, maxwidth, child_node):
        # Ensure root or fc is as least as wide as its first child
        if child_node:
            childwidth = NodeWidthCalc(child_node).calc()
            if childwidth > maxwidth:
                maxwidth = childwidth
        return maxwidth

    def LookAheadForNext_fc(self, i, nodes):
        for node,annotation in nodes[i:]:
            if annotation == 'fc':
                return node
            if annotation == 'root':
                return None
        return None

    def LookAheadForNext_tabs(self, i, nodes):
        result = []
        for node,annotation in nodes[i:]:
            if annotation == 'tab':
                result.append(node)
            else:
                break
        return result

    def next_node_is_fc(self, nodes, current_i):
        if current_i >= len(nodes) - 1:
            return False
        else:
            next_node, annotation = nodes[current_i + 1]
            return annotation == 'fc'

    def list_parents(self, rels_generalisation):
        parents = []
        for klass in rels_generalisation:
            parents += "[ " + klass + " ]"
        return parents

    def cr(self, n=1):
        return "\n" * n
    
    def main(self, graph, nodes_annotated_and_sorted=None):
        w = AsciiWorkspace(margin=7)
        
        """
        Calling graph.nodes_sorted_by_generalisation() gives us an annotated
        inheritance chain. We then process the nodes in that order, so that
        inheritance can be drawn top down (assuming single inheritance as the
        most common case). Update: Now handles multiple inheritance too.
        
        Note: an 'alias' is where you don't draw the whole class box but instead
        print the class inside square brackets e.g. [Fred].  We only draw aliases
        above fully drawn nodes, to show what they inherit from.  We also use
        aliases to depict composition associations.
        """
        #print [(node.id,annotation) for node,annotation in graph.nodes_sorted_by_generalisation]

        if not nodes_annotated_and_sorted:
            nodes_annotated_and_sorted = graph.nodes_sorted_by_generalisation
            
        NUM_LONER_ROOTS_PER_LINE = 3
        root_counter = 0
        
        INTRALINE = 2
        PADDING_ABOVE_ALIASES = 2
        row_margin = PADDING_ABOVE_ALIASES + INTRALINE
        row_top_padding = ""

        nodes = nodes_annotated_and_sorted
        
        s = ""
        i = 0
        for i in range(len(nodes)):
            node,annotation = nodes[i]

            if s:
                """ Make decision re what to do with the last node"""
                
                # Any root needs to be put on a fresh line, and start new node off with a header margin of \n\n
                # Unless the root is part of a bunch of root loners as controlled by NUM_LONER_ROOTS_PER_LINE
                if annotation == 'root':
                    w.AddColumn(s)
                    if root_counter <= 0 or self.next_node_is_fc(nodes, i):
                        w.Flush()
                        row_top_padding = self.cr(row_margin - PADDING_ABOVE_ALIASES)  # "\n\n"  # ONE, TWO
                        root_counter = NUM_LONER_ROOTS_PER_LINE
                    root_counter -= 1
                    s = self.cr(row_margin)  # "\n\n\n" # ONE, TWO, THREE
                
                # Any fc (first child) needs to be put on a fresh line, but no header margin cos want to glue to parent
                elif annotation == 'fc':
                    w.AddColumn(s)
                    w.Flush()
                    row_top_padding = ""
                    s = row_top_padding
                    root_counter = 0    # could potentially set to NUM_LONER_ROOTS_PER_LINE - 1 to keep more things on the same row but fc, tab, root sequence is tricky
                # Else tab need to be added to previous line, thus no Flush.
                else:
                    w.AddColumn(s)
                    s = row_top_padding
                    root_counter -= 1

            maxwidth = NodeWidthCalc(node).calc()
            # Ensure root or fc is as wide as its fc below it, so that parent nodes are not too thin and so generalisation line connects to parent properly.
            node_next_fc = None
            if annotation in ['fc', 'root']:
                node_next_fc = self.LookAheadForNext_fc(i+1, nodes)
                maxwidth = self.EnsureRootAsWideAsChild(maxwidth, node_next_fc)
            maxwidth += 2

            rels_composition, rels_generalisation = self.CalcRelations(node, graph)
        
            if rels_generalisation:
                if annotation == 'tab':
                    s += self.cr(PADDING_ABOVE_ALIASES)     # "\n"  # THREE
                    s += "".join(self.list_parents(rels_generalisation)).center(maxwidth, " ") + "\n"

                if annotation == 'root': #and len(rels_generalisation) > 1:   # List multiple parents as aliases when multiple inheritance
                    s += "".join(self.list_parents(rels_generalisation)).center(maxwidth, " ") + "\n"

                s += " . ".center(maxwidth, " ") + "\n"
                s += "/_\\".center(maxwidth, " ") + "\n"
                s += " | ".center(maxwidth, " ") + "\n"
                s += " | ".center(maxwidth, " ") + "\n"
                if annotation == 'fc':
                    s += (" | ".center(maxwidth, " ") + "\n") * (PADDING_ABOVE_ALIASES + 1)  # draw extra lines to match the 'tab' case where parents are listed, so that child nodes line up horizontally

            s += self.top_or_bottom_line(maxwidth)
            s += '|%s|' % node.id.center(maxwidth, " ") + "\n"

            self.pending_composition_line_output.extend(rels_composition)

            if hasattr(node, 'attrs') and node.attrs:
                s += self.attrs_or_meths(node.attrs, maxwidth)
            if hasattr(node, 'meths') and node.meths:
                s += self.attrs_or_meths(node.meths, maxwidth)

            s += self.top_or_bottom_line(maxwidth)

            # Add extra height by drawing a vertical line underneath current node
            # if any subsequent siblings are going to be pushing megarow to be taller
            # This way the generalisation line drawn later by the fc will actually join up.
            # Only need this if there is a fc coming up - hence the check for node_next_fc
            def height_of(node):
                result = len(node.meths) + len(node.attrs)
                if len(node.meths) and len(node.attrs):     # account for the extra dividing line if have both attrs and methods
                    result += 1
                return result
                
            if annotation in ['fc', 'root'] and node_next_fc:
                siblings = [node]
                siblings.extend(self.LookAheadForNext_tabs(i+1, nodes))
                max_megarow_height = max([height_of(sibling) for sibling in siblings])
                padding_needed = max_megarow_height - height_of(node)
                if padding_needed:
                    s += (" | ".center(maxwidth, " ") + "\n") * padding_needed  # long line drawn here

            s = s.rstrip()

        w.AddColumn(s)
        w.Flush()
        return w.contents
