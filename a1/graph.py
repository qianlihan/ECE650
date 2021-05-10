from street import Street
import re
from vertex import Vertex
from functions import check_intersection, check_med, linear_solver

class Graph:

    def __init__(self):
        self.st_dict = {}
        self.v_lst ={}
        self.special = set()
        #keep the track of the next available index
        self.index = 1


    def add(self, new_st):
        new_x = new_st.get_x()
        new_y = new_st.get_y()
        for st in self.st_dict.values():
            x = st.get_x()
            y = st.get_y()

            #for each segment of a street
            for i in range(len(x) - 1):
                p1 = (x[i], y[i])
                p2 = (x[i + 1], y[i + 1])
                for j in range(len(new_x) - 1):
                    p3 = (new_x[j], new_y[j])
                    p4 = (new_x[j + 1], new_y[j + 1])

                    intersection = check_intersection(p1, p2, p3, p4)
                    if intersection:

                        #check and add the endpoints
                        for end in [p1, p2]:
                            if end not in self.v_lst.keys():
                                self.v_lst[end] = Vertex(end, st.get_name(), None, self.index, True)
                                self.index +=1
                            elif not self.v_lst[end].endpoint_exist(st.get_name()):
                                old_index = self.v_lst[end].get_index()
                                self.v_lst[end].add(end, st.get_name(), None, old_index, True)

                        for end in [p3, p4]:
                            #corner case: 对顶角没考虑！！！
                            if end not in self.v_lst.keys():
                                self.v_lst[end] = Vertex(end, new_st.get_name(), None, self.index, True)
                                self.index +=1
                            elif not self.v_lst[end].endpoint_exist(new_st.get_name()):
                                old_index = self.v_lst[end].get_index()
                                self.v_lst[end].add(end, new_st.get_name(), None, old_index, True)
                        
                        
                        #check if it is an existing vertex
                        # two things to do:
                        # 1. add the vertices to its street
                        # 2. add the vertices to the v_dict           
                        if intersection in self.v_lst.keys():

                            #always use the key in the first node of the linked list
                            old_index = self.v_lst[intersection].get_index()
                            st.add_vertex(i, intersection, new_st.get_name(), old_index)
                            new_st.add_vertex(j, intersection, st.get_name(), old_index)
                            self.v_lst[intersection].add(intersection, st.get_name(), new_st.get_name(), old_index, False, st1_i = i, st2_i = j)
                        else:
                            st.add_vertex(i, intersection, new_st.get_name(), self.index)
                            new_st.add_vertex(j, intersection, st.get_name(), self.index)
                            self.v_lst[intersection] = Vertex(intersection, st.get_name(), new_st.get_name(), self.index, False, st1_i = i, st2_i = j)
                            self.index += 1

        self.st_dict[new_st.get_name()] = new_st

        
    def remove(self, old_st):
        old_st = old_st.upper()
        if old_st not in self.st_dict.keys():
            raise Exception()
        Street.all_names.remove(old_st)
        old_st = self.st_dict.pop(old_st)

        useless_vertex = []
        for key, vertex in self.v_lst.items():
            self.v_lst[key] = vertex.delete(old_st.get_name())
            if not self.v_lst[key]:
                useless_vertex.append(key)
        for i in useless_vertex:
            self.v_lst.pop(i)
        
        for key, value in self.st_dict.items():
            value.delete(old_st.get_name(), self.v_lst)


    def change(self, new_st):
        split_result = re.fullmatch(r'"(.*)" (.*)', new_st)
        temp = split_result.group(2).replace(" ","")
        if re.fullmatch(r'(\([-]?[0-9]+,[-]?[0-9]+\))*', temp):
            self.remove(split_result.group(1))
            self.add(Street(new_st))
        else: 
            raise Exception()

    def display(self):
        print("V = {")
        for (key, value) in self.v_lst.items():
            print("  {}".format(value.get_index()) +  ": ({:.2f}".format(key[0]) + ",{:.2f}".format(key[1]) + ")")
        print("}")
        print("E = {")
        output = set()
        for value in self.st_dict.values():
            value.print_edge(self.v_lst, output)
        print("}")
