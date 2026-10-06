// Create some sample data

using CompanyHierarchy;

var management = new Department { Name = "Management" };

var hardware = new Department { Name = "Hardware" };
var hardwareDevelopment = new Department { Name = "Hardware Development" };
var hardwareQa = new Department { Name = "Hardware QA" };
var hardwareSupport = new Department { Name = "Hardware Support" };
var hardwarePurchasing = new Department { Name = "Hardware Purchasing" };

var software = new Department { Name = "Software" };
var softwareDevelopment = new Department { Name = "Software Development" };
var softwareTesting = new Department { Name = "Software QA" };
var softwareSupport = new Department { Name = "Software Support" };

var it = new Department { Name = "IT" };
var marketing = new Department { Name = "Marketing" };
var sales = new Department { Name = "Sales" };
var customerSupport = new Department { Name = "Customer Support" };

management.AddDescendant(new Employee
{
    FirstName = "Alice",
    LastName = "Johnson",
    EmployeeId = "00001",
    Department = management,
    Role = "CEO",
    Salary = 120000
});

management.AddDescendant(new Employee
{
    FirstName = "Tina",
    LastName = "Lewis",
    EmployeeId = "11223",
    Department = management,
    Role = "CEO Assistant",
    Salary = 110000
});

hardware.AddDescendant(new Employee
{
    FirstName = "Bob",
    LastName = "Brown",
    EmployeeId = "54321",
    Department = hardware,
    Role = "Manager",
    Salary = 100000
});

hardwareDevelopment.AddDescendant(new Employee
{
    FirstName = "John",
    LastName = "Doe",
    EmployeeId = "12345",
    Department = hardwareDevelopment,
    Role = "Lead Engineer",
    Salary = 90000
});

hardwareDevelopment.AddDescendant(new Employee
{
    FirstName = "Jane",
    LastName = "Smith",
    EmployeeId = "67890",
    Department = hardwareDevelopment,
    Role = "Engineer",
    Salary = 80000
});

hardwareQa.AddDescendant(new Employee
{
    FirstName = "Alice",
    LastName = "Davis",
    EmployeeId = "11223",
    Department = hardwareQa,
    Role = "QA Engineer",
    Salary = 55000
});

hardwareSupport.AddDescendant(new Employee
{
    FirstName = "Charlie",
    LastName = "Wilson",
    EmployeeId = "44556",
    Department = hardwareSupport,
    Role = "Support Assistant",
    Salary = 50000
});

hardwarePurchasing.AddDescendant(new Employee
{
    FirstName = "Eve",
    LastName = "Taylor",
    EmployeeId = "77889",
    Department = hardwarePurchasing,
    Role = "Purchasing Agent",
    Salary = 65000
});

hardwareDevelopment.AddDescendant(hardwareQa);
hardware.AddDescendant(hardwareDevelopment);
hardware.AddDescendant(hardwareSupport);
hardware.AddDescendant(hardwarePurchasing);
management.AddDescendant(hardware);

software.AddDescendant(new Employee
{
    FirstName = "Frank",
    LastName = "Anderson",
    EmployeeId = "99887",
    Department = software,
    Role = "Manager",
    Salary = 95000
});

softwareDevelopment.AddDescendant(new Employee
{
    FirstName = "Grace",
    LastName = "Martinez",
    EmployeeId = "33445",
    Department = softwareDevelopment,
    Role = "Lead Engineer",
    Salary = 70000
});

softwareDevelopment.AddDescendant(new Employee
{
    FirstName = "Hank",
    LastName = "Garcia",
    EmployeeId = "55667",
    Department = softwareDevelopment,
    Role = "Engineer",
    Salary = 85000
});

softwareTesting.AddDescendant(new Employee
{
    FirstName = "Ivy",
    LastName = "Hernandez",
    EmployeeId = "88990",
    Department = softwareTesting,
    Role = "QA Engineer",
    Salary = 60000
});

softwareSupport.AddDescendant(new Employee
{
    FirstName = "Jack",
    LastName = "Lopez",
    EmployeeId = "22334",
    Department = softwareSupport,
    Role = "Support Assistant",
    Salary = 55000
});

softwareDevelopment.AddDescendant(softwareTesting);
software.AddDescendant(softwareDevelopment);
software.AddDescendant(softwareSupport);
management.AddDescendant(software);

it.AddDescendant(new Employee
{
    FirstName = "Kathy",
    LastName = "Gonzalez",
    EmployeeId = "44567",
    Department = it,
    Role = "Manager",
    Salary = 90000
});

it.AddDescendant(new Employee
{
    FirstName = "Leo",
    LastName = "Wilson",
    EmployeeId = "77890",
    Department = it,
    Role = "System Administrator",
    Salary = 70000
});

it.AddDescendant(new Employee
{
    FirstName = "Mia",
    LastName = "Martinez",
    EmployeeId = "11223",
    Department = it,
    Role = "Network Engineer",
    Salary = 80000
});

marketing.AddDescendant(new Employee
{
    FirstName = "Nina",
    LastName = "Anderson",
    EmployeeId = "33445",
    Department = marketing,
    Role = "Manager",
    Salary = 85000
});

marketing.AddDescendant(new Employee
{
    FirstName = "Oscar",
    LastName = "Thomas",
    EmployeeId = "55667",
    Department = marketing,
    Role = "Marketing Specialist",
    Salary = 60000
});

customerSupport.AddDescendant(new Employee
{
    FirstName = "Paul",
    LastName = "Jackson",
    EmployeeId = "88990",
    Department = customerSupport,
    Role = "Manager",
    Salary = 80000
});

customerSupport.AddDescendant(new Employee
{
    FirstName = "Quinn",
    LastName = "White",
    EmployeeId = "22334",
    Department = customerSupport,
    Role = "Support Specialist",
    Salary = 55000
});

sales.AddDescendant(new Employee
{
    FirstName = "Rita",
    LastName = "Harris",
    EmployeeId = "44567",
    Department = sales,
    Role = "Manager",
    Salary = 95000
});

sales.AddDescendant(new Employee
{
    FirstName = "Sam",
    LastName = "Clark",
    EmployeeId = "77890",
    Department = sales,
    Role = "Sales Associate",
    Salary = 60000
});

management.AddDescendant(it);
management.AddDescendant(marketing);
management.AddDescendant(sales);
management.AddDescendant(customerSupport);

Console.WriteLine(management);
