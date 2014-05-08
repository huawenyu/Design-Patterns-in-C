## Decorator vs Proxy

- Decorator get reference for decorated object (usually through constructor) while Proxy responsible to do that by himself.
- Proxy may not instantiate wrapping object at all (like this do ORMs to prevent unnecessary access to DB if object fields/getters are not used) while Decorator always hold link to actual wrapped instance.
- Proxy usually used by frameworks to add security or caching/lazing and constructed by framework (not by regular developer itself).
- Decorator usually used to add new behavior to old or legacy classes by developer itself based on interface rather then actual class (so it work on wide range of interface instances, Proxy is around concrete class).
