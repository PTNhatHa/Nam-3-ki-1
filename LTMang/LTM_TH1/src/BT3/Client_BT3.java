
package BT3;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import javax.swing.*;

public class Client_BT3 extends JFrame  {

	TextArea output;
	JTextField input;
	static Socket socket;
	static int stt = 1;
	public static void main(String[] args) throws Exception  {
		try {
			socket = new Socket("localhost", 7000);
			Client_BT3 chat = new Client_BT3(stt);
			stt++;
			chat.setVisible(true);
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	private void sendMessage() throws IOException
	{
		
		DataOutputStream dos = new DataOutputStream(socket.getOutputStream());
		String mess = input.getText();
		if(!mess.isEmpty())
		{
			dos.writeUTF(mess);
			dos.flush();
		}
	}
	Client_BT3(int stt)
	{
		this.setTitle("Client");
		this.setSize(500, 300);
		this.setDefaultCloseOperation(3);
		this.setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
		
		output = new TextArea();
		output.setEditable(false);
		this.add(output);

		JPanel p2 = new JPanel();
		p2.setLayout(new FlowLayout());
		input = new JTextField(45);
		p2.add(input);
		JButton b1 = new JButton("Send");
		new Thread(new Runnable() {
            public void run() {
                try {
                	DataInputStream din = new DataInputStream(socket.getInputStream());
                    while(true) {
                    	String remess = din.readUTF();
        				output.setText(output.getText() + "\n" + remess);
        				input.setText("");
                        Thread.sleep(1000);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
            }
        }).start();	
		b1.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				try {
					sendMessage();
				} catch (IOException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
			}
		});
		JButton b2 = new JButton("Close");
		b2.addActionListener((ActionListener) new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				System.exit(0);
			}
		});
		p2.add(b1);
		p2.add(b2);
		this.add(p2);
	}
}
