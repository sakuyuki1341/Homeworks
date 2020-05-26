class Student {
	private String id;		// 学籍番号
	private String name;	// 名前
	private int grade;		// 成績

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
	private String name;	// 課題名
	private String teacher;	// 担当者
	private int max;		// 最大履修者数
	private int num;		// 登録履修者数
	private Student[] st;	// Studentの配列

	public Lesson(String name, String teacher, int max) {
		this.name = name;
		this.teacher = teacher;
		this.max = max;
		this.num = 0;			// numは0に初期化
		st = new Student[max];	// 配列の確保(オブジェクトは別に生成する必要あり)
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
		// 学生の登録
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
// 以下は実行結果
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