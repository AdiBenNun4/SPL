import sqlite3
import atexit
from dbtools import Dao
 
# Data Transfer Objects:
class Employee(object):
    def __init__(self,id,name,salary,branche):
        self.id=id
        self.name=name
        self.salary=salary
        self.branche=branche
 
class Supplier(object):
    def __init__(self,id,name,contact_information):
        self.id=id
        self.name=name
        self.contact_information=contact_information

class Product(object):
    def __init__(self,id,description,price,quantity):
        self.id=id
        self.description=description
        self.price=price
        self.quantity=quantity

class Branche(object):
    def __init__(self,id,location,number_of_employees):
        self.id=id
        self.location=location
        self.number_of_employees=number_of_employees

class Activitie(object):
    def __init__(self,product_id, quantity,activator_id,date):
        self.product_id=product_id
        self.quantity=quantity
        self.activator_id=activator_id
        self.date=date

class EmployeesReport:
    def __init__(self, conn):
        self._conn = conn

    def __str__(self):
        c = self._conn.cursor()
        output = c.execute("""
                    SELECT employees.name,employees.salary,branches.location, SUM (Total_Sales_Income)
                    FROM(employees JOIN branches ON employees.branche = branches.id LEFT JOIN 
                    (SELECT activities.activator_id, products.price*activities.quantity*-1 AS Total_Sales_Income FROM
                    activities INNER JOIN products ON activities.product_id = products.id) ON employees.id=activator_id) GROUP BY employees.name
                    ORDER BY employees.name ASC;            
                """).fetchall()
        s=""
        for item in output:
            i3=item[3]
            if item[3] is None: i3=0
            s =s +"%s %s %s %g\n" % (item[0].decode(), float(item[1]), item[2].decode(), i3)
        return s[:-1]

#Repository
class Repository(object):
    

    def __init__(self):
        self._conn = sqlite3.connect('bgumart.db')
        self._conn.text_factory = bytes
        self.employees= Dao(Employee,self._conn)
        self.suppliers=Dao(Supplier,self._conn)
        self.products=Dao(Product,self._conn)
        self.branches=Dao(Branche,self._conn)
        self.activities=Dao(Activitie,self._conn)
        self.sales={}
        
        
    def _close(self):
        self._conn.commit()
        self._conn.close()
 
    def create_tables(self):
        self._conn.executescript("""
            DROP TABLE IF EXISTS employees;
            CREATE TABLE employees (
                id              INT         PRIMARY KEY,
                name            TEXT        NOT NULL,
                salary          REAL        NOT NULL,
                branche    INT REFERENCES branches(id)
            );
            DROP TABLE IF EXISTS suppliers;
            CREATE TABLE suppliers (
                id                   INTEGER    PRIMARY KEY,
                name                 TEXT       NOT NULL,
                contact_information  TEXT
            );
            DROP TABLE IF EXISTS products;
            CREATE TABLE products (
                id          INTEGER PRIMARY KEY,
                description TEXT    NOT NULL,
                price       REAL NOT NULL,
                quantity    INTEGER NOT NULL
            );
            DROP TABLE IF EXISTS branches;
            CREATE TABLE branches (
                id                  INTEGER     PRIMARY KEY,
                location            TEXT        NOT NULL,
                number_of_employees INTEGER
            );
            DROP TABLE IF EXISTS activities;
            CREATE TABLE activities (
                product_id      INTEGER REFERENCES products(id),
                quantity        INTEGER NOT NULL,
                activator_id    INTEGER NOT NULL,
                date            TEXT    NOT NULL
            );
        """)

        

    def execute_command(self, script: str) -> list:
        return self._conn.cursor().execute(script).fetchall()

    def ActivityReports(self):
        output= self._conn.cursor().execute("""SELECT activities.date, products.description, activities.quantity, employees.name, suppliers.name FROM activities
        JOIN products ON products.id = activities.product_id 
        LEFT JOIN employees ON employees.id = activities.activator_id
        LEFT JOIN suppliers ON suppliers.id = activities.activator_id
        """).fetchall()
        s=""
        for item in output:
            i3=None
            i4=None
            if item[3] is not None: i3=item[3].decode()
            if item[4] is not None: i4=item[4].decode()
            s =s +"(%s, '%s', %d, %s, '%s')\n" % (item[0].decode(), item[1].decode(), item[2], i3, i4)
        return s[:-1]
        
        
 
# singleton
repo = Repository()
atexit.register(repo._close)


