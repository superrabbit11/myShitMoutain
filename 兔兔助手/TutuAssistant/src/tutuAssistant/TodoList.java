package tutuAssistant; 
import java.util.Scanner;

public class TodoList {  
	protected static final int MAXSIZE = 10; // 最大表长  
	protected String[] todos = new String[MAXSIZE]; // new一个
	protected int todoCount = 0; // 记录当前已存储的待办事项数量  
  
    public void add() {  
        if (todoCount >= MAXSIZE) {  
            System.out.println("待办事项已满，无法添加更多！");  
            return;  
        }  
          
        Scanner scanner = new Scanner(System.in);  
        System.out.print("请输入待办事项：");  
        String todo = scanner.nextLine();  
        todos[todoCount] = todo;  
        todoCount++;  
        System.out.println("待办事项已添加：" + todo);  
    }  
  
    public void show() {  
        if (todoCount == 0) {  
            System.out.println("今日无待办事项！");  
            return;  
        }  
          
        System.out.println("今日待办事项：");  
        for (int i = 0; i < todoCount; i++) {  
            System.out.println((i + 1) + ". " + todos[i]);  
        }  
    }  
}  

