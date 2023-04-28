from persistence import *
from dbtools import *


def main():
    print('Activities')
    a=repo.activities.find_all()
    for x in a:
        s="(%d, %s, %s, %s)" % (x.product_id,x.quantity,x.activator_id,x.date.decode())
        print(s)
    print('Branches')
    bra = repo.branches.find_all()
    for x in bra:
        s = "(%d, '%s', %d)" % (x.id, x.location.decode(), x.number_of_employees)
        print(s)
    print('Employees')
    emp = repo.employees.find_all()
    for x in emp:
        s = "(%d, '%s', %s, %g)" % (x.id, x.name.decode(), float(x.salary), x.branche)
        print(s)
    print('Products')
    pro = repo.products.find_all()
    for x in pro:
        s = "(%d, '%s', %s, %d)" % (x.id,x.description.decode(),float(x.price),x.quantity)
        print(s)
    print('Suppliers')
    sup = repo.suppliers.find_all()
    for x in sup:
        s = "(%d, '%s', %s)" % (x.id, x.name.decode(), x.contact_information.decode())
        print(s)

    print('\nEmployees report')
    print((EmployeesReport(repo._conn)))

    print('\nActivities reports')
    print(repo.ActivityReports())


if __name__ == '__main__':
     main()