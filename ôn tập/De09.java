import java.util.LinkedList;
import java.util.Scanner;

public class De09 {
        // Danh sách liên kết S
        static LinkedList<Integer> S = new LinkedList<>();

        // Biến kiểm tra Task1 còn chạy hay không
        static volatile boolean running = true;

        // TASK1: Nhập số từ bàn phím
        static void task1() {
                Scanner sc = new Scanner(System.in);
                while (true) {
                        System.out.print("Nhap so (-1 de dung): ");
                        int x = sc.nextInt();
                        if (x == -1) {
                                running = false;
                                break;
                        }
                        synchronized (S) {
                                S.add(x);
                        }
                }
                sc.close();
        }

        // TASK2: Hiển thị danh sách liên tục cho tới khi Task1 kết thúc
        static void task2() {
                while (running) {
                        synchronized (S) {
                                System.out.print("Danh sach S: ");
                                for (int x : S) {
                                        System.out.print(x + " ");
                                }
                                System.out.println();
                        }

                        try {
                                Thread.sleep(1000); // mỗi giây hiển thị 1 lần
                        } catch (InterruptedException e) {
                                e.printStackTrace();
                        }
                }

                // In lần cuối khi Task1 kết thúc
                synchronized (S) {
                        System.out.print("Danh sach cuoi: ");
                        for (int x : S) {
                                System.out.print(x + " ");
                        }
                        System.out.println();
                }
        }

        public static void main(String[] args) {
                // Luồng Task1
                Thread t1 = new Thread(De09::task1);

                // Luồng Task2
                Thread t2 = new Thread(De09::task2);

                // Chạy 2 task không đồng bộ
                t1.start();
                t2.start();
        }
}