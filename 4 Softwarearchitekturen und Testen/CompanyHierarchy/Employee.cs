namespace CompanyHierarchy;

public class Employee : IOrganizationUnit
{
    public required string FirstName { get; set; }

    public required string LastName { get; set; }

    public required string EmployeeId { get; init; }

    public required Department Department { get; set; }

    public required string Role { get; set; }

    public required int Salary { get; set; }

    public override string ToString()
    {
        return $"Employee: {LastName}, {FirstName} ({EmployeeId}), Department: {Department.Name}, Role: {Role}, Salary: {Salary}";
    }
}
