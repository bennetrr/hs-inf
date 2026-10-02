import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public class EmployeeAdministration {
	List<Employee> employees = new ArrayList<Employee>();

	public EmployeeAdministration(List<Employee> list) {
		employees.addAll(list);
	}

	public void add(Employee e) {
		employees.add(e);
	}

	public List<Employee> filter(Predicate<Employee> p) {
		 return employees.stream().filter(p).toList();
	}
}
