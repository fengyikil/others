package test;
public class Man{
	private int old=0;
	public void test()
	{
		Man man = new Man();
		man.old = 5;
		System.out.println(""+man.old);
	}
	public static void main(String[] args){
		new Test().test();
	}
}