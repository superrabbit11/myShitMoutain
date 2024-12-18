/******
 实事求是来讲，这个类三分写，七分查资料……
 主要是想试试哈哈哈哈^_^
	******/
package tutuAssistant;
import java.util.Scanner;  
import java.util.concurrent.TimeUnit;  //用于暂停，实现倒计时功能
  
public class Tomato_todo {  
    public static void countdown(int totaltime) {
        for (int i = totaltime; i >= 0; i--) {  
            int minutes = i / 60;  
            int seconds = i % 60;  
            String timeFormat = String.format("%02d:%02d", minutes, seconds); // 输出时间为几分几秒的样式 
            System.out.println("\r倒计时: " + timeFormat); // \r 用于回到行首，实现覆盖效果
            try {  
                TimeUnit.SECONDS.sleep(1); //暂停一秒，实现在控制台上展示过去时间 
            } catch (InterruptedException e) {  
                e.printStackTrace();  
                System.out.println("倒计时被中断。");  
                return;  
            }   
    }  
        System.out.println("倒计时结束！"); 
    }
}

