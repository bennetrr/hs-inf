package de.hsco.ads.uebung05;

public class Student implements IStudent {
    private final String name;

    public Student(String name) {
        this.name = name;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public final boolean equals(Object o) {
        if (this == o)
            return true;
        if (!(o instanceof Student student))
            return false;

        return name.equals(student.name);
    }

    @Override
    public int hashCode() {
        return name.hashCode();
    }
}
