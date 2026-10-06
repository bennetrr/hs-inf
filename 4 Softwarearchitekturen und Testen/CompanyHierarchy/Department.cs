namespace CompanyHierarchy;

public class Department : IOrganizationUnit
{
    public required string Name { get; set; }

    public List<IOrganizationUnit> Descendants { get; } = [];

    public void AddDescendant(IOrganizationUnit descendant)
    {
        Descendants.Add(descendant);
    }

    public override string ToString()
    {
        return $"Department: {Name}:\n    {string.Join("\n", Descendants).ReplaceLineEndings("\n    ")}";
    }
}
