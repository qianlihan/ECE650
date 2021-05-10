import re
from vertex import Vertex

class Street:
    #one name, a list for x, a list for y
    all_names = []

    class intersect:
        def __init__(self, xy, st, index):
            self.x = xy[0]
            self.y = xy[1]
            self.st = [st]
            self.index = index
    
        def get_xy(self):
            return (self.x, self.y)

    def __init__(self, userinput):
        split_result = re.match(r'"(.*)" (.*)', userinput)

        #eliminate all the space
        coordinations = split_result.group(2).replace(" ","")
        
        #check whether the style is correct
        if re.fullmatch(r'(\([-]?[0-9]+,[-]?[0-9]+\))*', coordinations) and split_result.group(1).upper() not in Street.all_names:
            self.name = split_result.group(1).upper()
            #get the numbers in pair
            pattern = re.compile(r'([-]?[0-9]+),([-]?[0-9]+)')
            self.x, self.y = [], []
            for (x, y) in re.findall(pattern, coordinations):
                self.x.append(int(x))
                self.y.append(int(y))
            self.vertex = {}
            Street.all_names.append(split_result.group(1).upper())
        else:
            raise Exception()

    def get_x(self):
        return self.x

    def get_y(self):
        return self.y

    def get_name(self):
        return self.name

    def add_vertex(self, street_index, xy, st, vertex_index):
        #add a vertex to the dict based on the segment index, in a order

        new_intersect = self.intersect(xy, st, vertex_index)
        if street_index not in self.vertex.keys():
            self.vertex[street_index] = [new_intersect] 
        else:
            self.vertex[street_index].append(new_intersect)
    
    def delete(self, st, v_lst):      
        useless_key = []
        for (key, intersections) in self.vertex.items():  
            for each_intersection in intersections:
                each_intersection.st = [i for i in each_intersection.st if st != i]
            
            #eliminate the elements if its st component is null
            self.vertex[key] = [i for i in intersections if i.st]
            if not self.vertex[key]:
                useless_key.append(key)
        for item in useless_key:
            self.vertex.pop(item)
            
        for i in range(len(self.x)):    
            if i not in self.vertex.keys() and (i - 1) not in self.vertex.keys():
                xy = self.x[i], self.y[i]
                if xy in v_lst.keys():
                    v_lst[xy] = v_lst[xy].delete(self.name)
                    if not v_lst[xy]:
                        v_lst.pop(xy)

    def print_edge(self, v_lst, output):

        for i in range(len(self.x) - 1):
            if i in self.vertex.keys():
                start = self.x[i], self.y[i]
                end = self.x[i + 1], self.y[i + 1]
                temp = [i.get_xy() for i in self.vertex[i]]
                temp.extend([start, end])
                temp = set(temp)
                temp = list(temp)
                if start[0] == end[0]:
                    temp.sort(key = lambda x: x[1])
                else:
                    temp.sort(key = lambda x: x[0])
                for j in range(len(temp) - 1):
                    first = v_lst[temp[j]].get_index()
                    second = v_lst[temp[j + 1]].get_index()
                    if (first, second) not in output:
                        print("<" +  str(first) + "," + str(second) +">,", end="")
                        output.add((first, second))