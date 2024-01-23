package BT2;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Stack;

public class Server_BT2 {

	public static void main(String[] args) throws Exception
	{
		ServerSocket socketServer = new ServerSocket(7000);
		System.out.println("Server is started");
		while(true)
		{
			Socket socket = socketServer.accept();
			int count = 0;
			new ClientHandlder(socket, count).start();;
			count++;
		}
	}
}

class ClientHandlder extends Thread {
	Socket socketServer;
	DataInputStream din;
	DataOutputStream dos;
	int count;
	
	public ClientHandlder(Socket socket, int c) throws IOException{
		this.socketServer = socket;
		din = new DataInputStream(socketServer.getInputStream());
		dos = new DataOutputStream(socketServer.getOutputStream());
		count = c;
	}
	public void run()
	{
		try {
			while(true)
			{
				String st = din.readUTF();
				String msg = "= " + String.valueOf(evaluate(st));
				dos.writeUTF(msg);
				dos.flush();
			}
		} catch (IOException e) {
			//e.printStackTrace();
		}
	}
	public static boolean delim(char c) {
        return c == ' ';
    }

    public static boolean is_op(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    public static int priority(char op) {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return -1;
    }

    public static void process_op(Stack<Double> st, char op) {
        double r = st.pop();
        double l = st.pop();
        switch (op) {
            case '+': st.push(l + r); break;
            case '-': st.push(l - r); break;
            case '*': st.push(l * r); break;
            case '/': st.push(l / r); break;
        }
    }

    public static double evaluate(String s) {
        Stack<Double> st = new Stack<>();
        Stack<Character> op = new Stack<>();
        for (int i = 0; i < s.length(); i++) {
            if (delim(s.charAt(i)))
                continue;

            if (s.charAt(i) == '(') {
                op.push('(');
            } else if (s.charAt(i) == ')') {
                while (op.peek() != '(') {
                    process_op(st, op.peek());
                    op.pop();
                }
                op.pop();
            } else if (is_op(s.charAt(i))) {
                char cur_op = s.charAt(i);
                while (!op.empty() && priority(op.peek()) >= priority(cur_op)) {
                    process_op(st, op.peek());
                    op.pop();
                }
                op.push(cur_op);
            } else {
                double number = 0;
                while (i < s.length() && Character.isDigit(s.charAt(i)))
                    number = number * 10 + s.charAt(i++) - '0';
                --i;
                st.push(number);
            }
        }

        while (!op.empty()) {
            process_op(st, op.peek());
            op.pop();
        }
        return st.peek();
    }
}

