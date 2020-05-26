class Student {
	private String id;		// �w�Дԍ�
	private String name;	// ���O
	private int grade;		// ����

	public Student(String id, String name, int grade) {
		this.id = id;
		this.name = name;
		this.grade = grade;
	}

	public void print() {
		System.out.println("ID   : " + id);
		System.out.println("Name : " + name);
		System.out.println("Grade: " + grade);
	}
	public void printShort() {
		System.out.println(id + ", " + name + ", " + grade);
	}
}

class Lesson {
	private String name;	// �ۑ薼
	private String teacher;	// �S����
	private int max;		// �ő嗚�C�Ґ�
	private int num;		// �o�^���C�Ґ�
	private Student[] st;	// Student�̔z��

	public Lesson(String name, String teacher, int max) {
		this.name = name;
		this.teacher = teacher;
		this.max = max;
		this.num = 0;			// num��0�ɏ�����
		st = new Student[max];	// �z��̊m��(�I�u�W�F�N�g�͕ʂɐ�������K�v����)
	}
	public void add(Student s) {
		st[this.num++] = s;
	}
	public void print() {
		System.out.println("Lesson            : " + name);
		System.out.println("Teacher           : " + teacher);
		System.out.println("Number of Students: " + num);
		for (int i = 0; i < num; i++) {
			st[i].printShort();
		}
		System.out.println("----------");
	}
}


class Main {
	public static void main(String[] args) {
		// �w���̓o�^
		Student[] st = new Student[4];
		st[0] = new Student("012200", "Dentsu Taro", 80);
		st[1] = new Student("012205", "Uec Jiro", 54);
		st[2] = new Student("012207", "Chofu Saburo", 70);
		st[3] = new Student("012210", "Enshu Shiro", 60);

		Lesson ls = new Lesson("Pro Enshu", "Yanai", 4);
		for (int i = 0; i < 4; i++) {
			ls.add(st[i]);
		}
		ls.print();
	}
}

// ------------------
// �ȉ��͎��s����
// ------------------
/*
Lesson            : Pro Enshu
Teacher           : Yanai
Number of Students: 4
012200, Dentsu Taro, 80
012205, Uec Jiro, 54
012207, Chofu Saburo, 70
012210, Enshu Shiro, 60
----------
*/