import java.util.*;

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

	public String getId() {
		return id;
	}
}

class Lesson {
	private String name;			// �ۑ薼
	private String teacher;			// �S����
	private int max;				// �ő嗚�C�o�^��
	private int num;				// �o�^���C�Ґ�
	private ArrayList<Student> st;	// Student�̔z��

	public Lesson(String name, String teacher, int max) {
		this.name = name;
		this.teacher = teacher;
		this.max = max;
		this.num = 0;			// num��0�ɏ�����
		st = new ArrayList<Student>();	// �z��̊m��(�I�u�W�F�N�g�͕ʂɐ�������K�v����)
	}
	public void add(Student s) {
		String id0 = s.getId();
		num++;
		for (int i = 0; i < st.size(); i++) {
			Student s0 = st.get(i);
			// id0���傫��ID�𔭌�
			if (id0.compareTo(s0.getId()) < 0) {
				// i�Ԗڂ�s��}��
				st.add(i, s);
				return;
			}
		}
		// �ǉ������w���̊w�Дԍ�����ԑ傫���Ƃ�
		// ���X�g�̍Ō���ɕt��������
		st.add(s);
	}
	public void print() {
		System.out.println("Lesson            : " + name);
		System.out.println("Teacher           : " + teacher);
		System.out.println("Number of Students: " + num);
		for (int i = 0; i < num; i++) {
			Student s_tmp = st.get(i);
			s_tmp.printShort();
		}
		System.out.println("----------");
	}
}

class Main {
	public static void main(String[] args) {
		// �w���̓o�^
		Student[] st = new Student[6];
		st[0] = new Student("012200", "Dentsu Taro", 80);
		st[1] = new Student("012210", "Enshu Shiro", 60);
		st[2] = new Student("012207", "Chofu Saburo", 70);
		st[3] = new Student("012205", "Uec Jiro", 54);
		st[4] = new Student("012160", "Taito Rokuro", 100);
		st[5] = new Student("012218", "Namco Goro", 78);

		Lesson ls = new Lesson("Pro Enshu", "Yanai", 4);
		for (int i = 0; i < 6; i++) {
			ls.add(st[i]);
		}
		ls.print();
	}
}

//-------------------
// �ȉ����s����
//-------------------
/*
$ java Main
Lesson            : Pro Enshu
Teacher           : Yanai
Number of Students: 6
012160, Taito Rokuro, 100
012200, Dentsu Taro, 80
012205, Uec Jiro, 54
012207, Chofu Saburo, 70
012210, Enshu Shiro, 60
012218, Namco Goro, 78
----------
*/
/*
���s�������ʁA������Ə����������珇�ɕ���ł��鎖��������B
*/