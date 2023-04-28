from persistence import *

import sys

def main(args : list):
    inputfilename : str = args[1]
    configfile= open(inputfilename,"r")
    for line in configfile:
        splittedline =line.split(", ")
        if(int(splittedline[1]) != 0):
            c=repo._conn.cursor()
            c.execute("""SELECT * FROM products WHERE id = ?
            """,[int(splittedline[0]),])
            current=Product(*c.fetchone())
            if (current.quantity + int(splittedline[1]) >= 0):
                current.quantity=current.quantity+int(splittedline[1])
                c.execute("""DELETE FROM products WHERE id = ?
                 """,[int(splittedline[0]),])
                repo.products.insert(current)
                repo.activities.insert(Activitie(splittedline[0],splittedline[1],splittedline[2],splittedline[3][:-1]))
                if (int(splittedline[1])<0):
                    repo.sales[int(splittedline[2])]=repo.sales.get(int(splittedline[2]),0)-(float(splittedline[1])*float(current.price)) #Updates employee's sales record


if __name__ == '__main__':
    main(sys.argv)