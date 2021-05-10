class Vertex:
    def __init__(self, xy, st1, st2, index, is_endpoint, st1_i = None, st2_i = None):
        self.index =index
        self.xy = xy
        self.is_endpoint = is_endpoint
        self.st1 = st1
        self.st2 = st2
        self.next = None
        self.st1_i = st1_i
        self.st2_i = st2_i

    def next(self):
        return self.next

    def get_index(self):
        return self.index

    def get_st1_i(self):
        return self.st1_i

    def get_st2_i(self):
        return self.st2_i


    def add(self, xy, st1, st2, index, is_endpoint, st1_i = None, st2_i = None):
        current = self
        while current.next:
            if current.xy == xy and current.st1 == st1 and current.st2 == st2 and current.index == index and current.is_endpoint == is_endpoint and current.st1_i == st1_i and current.st2_i == st2_i:
                return
            elif current.xy == xy and current.st1 == st2 and current.st2 == st1 and current.index == index and current.is_endpoint == is_endpoint and current.st1_i == st2_i and current.st2_i == st1_i:
                return
            current = current.next
        current.next = Vertex(xy, st1, st2, index, is_endpoint, st1_i, st2_i)

    def endpoint_exist(self, st):
        current = self
        while current:
            if current.is_endpoint and current.st1 == st:
                return True
            current = current.next
        return False

    def delete(self, old_st_name):
        current = self
        while current:
            if current.st1 == old_st_name or current.st2 == old_st_name:
                if current is self:
                    self = self.next
                else:
                    prev.next = current.next
            prev =current
            current = current.next
        return self

    def reset_index(self, new_index):
        current = self
        while current:
            current.index = new_index
            current = current.next

    