class AsciiWorkspace:
    """
    Looks after organising things in rows and columns with appropriate padding.
    You send it chunks of text and flush/newline commands and it will appear in
    a nice grid format. 
    """
    def __init__(self, margin=3):
        self.contents = ""    # TODO rename _contents
        self.margin = margin
        self._Init()
        
    def _Init(self):
        self.curr = []         # TODO rename megarow
        self.curr_height = 0   # TODO rename megarow_height
        self.curr_width = 0    # TODO rename megarow_indent
        
    def _CalcMargin(self):
        if not self.curr:
            return 0
        else:
            return self.margin

    def _Pad1(self, incoming_height, incoming_maxwidth, margin):
        """
        pad upto existing megarow_height, using incoming_maxwidth spaces
        """
        assert incoming_height <= self.curr_height
        for row in range(incoming_height, self.curr_height):
            self.curr[row] += (" "*incoming_maxwidth + margin*" ")

    def _ExpandAndPad2(self, incoming_height, incoming_maxwidth):
        """
        expand past existing megarow_height, using megarow_indent spaces
        """
        did_expand = False
        if incoming_height > self.curr_height:
            for row in range(incoming_height - self.curr_height):
                self.curr.append(" "*self.curr_width)
            did_expand = True
            self.curr_height = incoming_height
        return did_expand

    def _Add(self, lines, height, maxwidth, margin):
        for row in range(height):
            self.curr[row] += "%s%-*s" % (margin*" ", maxwidth, lines[row])
        
    # Public Methods
    
    def Flush(self):
        self.contents += "\n".join(self.curr) + "\n"
        self._Init()

    def AddColumn(self, str):
        lines = str.split("\n")
        
        maxwidth = max([len(line) for line in lines])
        height = len(lines)
        margin = self._CalcMargin()

        did_expand = self._ExpandAndPad2(height, maxwidth)
        self._Add(lines, height, maxwidth, margin)
        if not did_expand:
            self._Pad1(height, maxwidth, margin)
                
        self.curr_width += maxwidth+margin

    @property
    def Contents(self):
        return self.contents
            
    
if __name__ == '__main__':
    w = AsciiWorkspace()
    
    s = ""
    s += "hi there\n"
    s += "this is a fantastic test"
    
    w.AddColumn(s)
    
    s = ""
    s += "this is some more info\n"
    s += "which is in column 2\n"
    s += "and adds an extra line"
    
    w.AddColumn(s)

    s = "\n"
    s += "this is the third set of info\n"
    s += "which is back in column 1 again"

    w.Flush()
    w.AddColumn(s)

    w.Flush()
    print w.Contents
    
    print "="*50

    w = AsciiWorkspace()

    s = "aaaaaaaaaaaaa\n"
    s += "bbbbbbbbbbbbb"
    w.AddColumn(s)

    s = "ccccccc\n"
    s += "dddddddd"
    w.AddColumn(s)
    
    s = "eeeeeeeeeeeeeee\n"
    s += "fffffffffffffffff\n"
    s += "ggggggggggggggggg\n"
    s += "hhhhhhhhhhhhhhhhh"
    w.AddColumn(s)

    w.Flush()
    print w.Contents

    print "done"
    