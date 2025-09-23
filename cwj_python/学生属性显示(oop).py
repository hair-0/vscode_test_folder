class Student:
    def __init__(self, name, age, type, last_field):
        self.Name = name
        self.Age = int(age)
        self.Type = type
        self.Specialty = None
        self.Direction = None

        if type == 'Undergraduate':
            self.Specialty = last_field
        elif type == 'Graduate':
            self.Direction = last_field

    def get_attribute(self, attribute_name):
        if attribute_name == 'Name':
            return self.Name
        elif attribute_name == 'Age':
            return self.Age
        elif attribute_name == 'Type':
            return self.Type
        elif attribute_name == 'Specialty':
            if self.Type == 'Undergraduate':
                return self.Specialty
            else:
                return None
        elif attribute_name == 'Direction':
            if self.Type == 'Graduate':
                return self.Direction
            else:
                return None
        else:
            return None

students_dict = {}

N = int(input())

for _ in range(N):
    line = input().split()
    name, age, type, last_field = line
    students_dict[name] = Student(name, age, type, last_field)

M = int(input())

for _ in range(M):
    query_line = input().split()
    query_name = query_line[0]
    query_attribute = query_line[1]

    if query_name in students_dict:
        student = students_dict[query_name]
        result = student.get_attribute(query_attribute)

        if result is not None:
            print(result)
        else:
            print('none')
    else:
        print('none')