package tutuAssistant;
import java.util.Scanner;
import java.util.Random;//生成随机数
import java.util.concurrent.TimeUnit;//用于番茄钟暂停对准时间

public class TutuAssistant {
	public static void main(String[] args) { 
        Scanner scanner = new Scanner(System.in);
        AccountBook book = new AccountBook(); //进行对象实例化
        TodoList todoList = new TodoList();
        Tomato_todo Tomato_todo = new Tomato_todo();
        
        //初始界面
        System.out.println(" (\\__/)");
        System.out.println("( • - •)");
        System.out.println(" / つ️🧧");
        String text = "TutuAssistant（兔兔助手）";
        int width = text.length() + 4; // 矩形框的宽度
        int height= 3; // 矩形框的高度，包括顶部、底部和文本行

        // 打印顶部边框
        for (int i = 0; i < width; i++) {
            System.out.print("-");
        }
        System.out.println();

        // 打印文本行
        System.out.print("♥" + text + "♥"); // 打印文本
        System.out.println();

        // 打印底部边框
        for (int i = 0; i < width; i++) {
            System.out.print("-");
        }
        System.out.println();
   
        
        System.out.println("bb你具体要干嘛呢？");
        System.out.println("1. 闲聊");  
        System.out.println("2. 待办清单");  
        System.out.println("3. 兔兔账本"); 
        System.out.println("4. 番茄钟");
        int function=scanner.nextInt();

        
        //1、实现聊天功能
        while(function==1){
        	Random random = new Random();//随机回答
            String[] responses = {
                "你要唠这个，我可就不困了",
                "那你说说怎么回事啊",
                "这样啊",
                "哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈哈",
                "我服了",
                "抱抱你ww",
                "诶",
                "哦"
            };
            int count = 1;
            System.out.println("兔兔：来给我讲讲今天发生了什么吧！！（笑）");
            for(int i=0;i<5;i++) {
                String input = scanner.nextLine();
                if(i<5){
                	int responseIndex = random.nextInt(responses.length);
                    System.out.println("兔兔：" + responses[responseIndex]);
            }
            }
            //引导使用助手功能，不再闲聊
            System.out.println("兔兔：原来如此，那有什么我能帮你的吗？");  
            System.out.println("2. 待办清单");  
            System.out.println("3. 兔兔账本"); 
            System.out.println("4. 番茄钟");
            function=scanner.nextInt();
        }
        
        

        //2、实现待办清单功能
        while (function==2) {  
            System.out.println("请选择操作：");  
            System.out.println("1. 添加待办事项");  
            System.out.println("2. 查看待办事项");  
            System.out.println("3. 退出程序");  
            int choice = scanner.nextInt();  
            scanner.nextLine(); // 消耗掉输入后的换行符  
              
            switch (choice) {  
                case 1:  
                    todoList.add();  
                    break;  
                case 2:  
                    todoList.show();  
                    break;  
                case 3:  
                    System.out.println("程序已退出。");  
                    return;  
                default:  
                    System.out.println("无效的选择，请重新输入！");  
            }  
        } 
        
        //3、实现兔兔账本功能
        while(function==3){  
            System.out.println("欢迎使用兔兔账本！请问你要：");  
            System.out.println("1. 增加收入记录");  
            System.out.println("2. 增加支出记录");  
            System.out.println("3. 显示收入记录");  
            System.out.println("4. 显示支出记录");  
            System.out.println("5. 查看结余");  
            System.out.println("6. 退出");  
  
            int choice = scanner.nextInt();  
            switch (choice) {  
                case 1:  
                    System.out.print("这次你赚了：");  
                    double incomeAmount = scanner.nextDouble();  
                    book.addIncome(incomeAmount);  
                    break;  
                case 2:  
                    System.out.print("这次你花了：");  
                    double expenseAmount = scanner.nextDouble();  
                    book.addExpense(expenseAmount);  
                    break;  
                case 3:  
                    book.showincome();  
                    break;  
                case 4:  
                    book.showexpense();  
                    break;  
                case 5:  
                    System.out.println("现在你还剩下：" + book.residue());  
                    break;  
                case 6:  
                    break;  
                default:  
                    System.out.println("输的什么狗屎，重新输");  
            }  
        } 
        
      //4、实现番茄钟功能
        System.out.print("开始专注学习啦！！！₍ᐢ‥ᐢ₎ ♡ \n");  
        System.out.print("请输入需要学习的时长（分钟）: \n");  
        int minutes = scanner.nextInt();  
        int totaltime = minutes * 60; // 将分钟转换为秒  
        scanner.close();  
        
        //实现番茄钟功能
        Tomato_todo.countdown(totaltime);
        
	}    
}

