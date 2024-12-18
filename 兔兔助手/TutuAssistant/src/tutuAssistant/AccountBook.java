package tutuAssistant;  
  
public class AccountBook {  
	protected double[] income;  
	protected double[] expense;  
	protected int incomeCount = 0;//收入笔数
	protected int expenseCount = 0;//支出笔数
	protected static final int MAXSIZE = 10000;//最大表长
  
	protected AccountBook() {
    	//创建动态顺序表（既然没报错就说明JAVA也是这么做的！）
        income = new double[MAXSIZE]; 
        expense = new double[MAXSIZE];  
    }  
  
    // 添加收入  
	protected void addIncome(double amount) {  
        if (incomeCount < MAXSIZE) {  
            income[incomeCount] = amount;  
            incomeCount++;  
            System.out.println("哈哈，恭喜你赚了：" + amount);  
        } else {  
            System.out.println("存储不够了，不好意思以后再赚吧QAQ");  
        }  
    }  
  
    // 添加支出  
	protected void addExpense(double amount) {  
        if (expenseCount < MAXSIZE) {  
            expense[expenseCount] = amount;  
            expenseCount++;  
            System.out.println("你怎么又用了：" + amount);  
        } else {  
            System.out.println("账本写满了！！你个穷鬼别用钱了！！！");  
        }  
    }  
  
    // 显示所有收入记录  
	protected void showincome() {  
        System.out.println("收入情况：");  
        for (int i = 0; i < incomeCount; i++) {  
            System.out.println("记录 " + (i + 1) + ": " + income[i]);  
        }  
    }  
  
    // 显示所有支出记录  
	protected void showexpense() {  
        System.out.println("支出情况：");  
        for (int i = 0; i < expenseCount; i++) {  
            System.out.println("记录 " + (i + 1) + ": " + expense[i]);  
        }  
    }  
  
    // 计算结余  
	protected double residue() {  
        double totalIncome = 0;  
        double totalExpense = 0;  
        for (int i = 0; i < incomeCount; i++) {  
            totalIncome += income[i];  
        }  
        for (int i = 0; i < expenseCount; i++) {  
            totalExpense += expense[i];  
        }  
        return totalIncome - totalExpense;  
    }  
}  
