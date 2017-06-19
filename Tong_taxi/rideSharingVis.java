/*
	\author: 	Trasier
	\date:		2017.6.16
	\log锛�		
*/


import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.io.*;
import java.util.*;
import java.security.*;

import javax.swing.*;
import javax.imageio.ImageIO;

import java.lang.*;

// ------------- class Point ------------------------------
class Pnt {
    public static final double eps = 1e-4;
    public double x,y;
	
    public Pnt() {};
    public Pnt(double x1, double y1) {
        x = x1;
        y = y1;
    }
	
    public boolean equals(Pnt other) {
        return dcmp(x-other.x)==0 && dcmp(y-other.y)==0;
    }

    public double toLength(Pnt other) {
        return Math.sqrt((x-other.x)*(x-other.x) + (y-other.y)*(y-other.y));
    }

    private int dcmp(double x) {
        if (Math.abs(x) < eps)
            return 0;
        return x>0 ? 1 : -1;
    }
}

class Order {
	public double t;
	public int sid, eid;
	
	public Order() {}
	
	public Order(double t1, int sid1, int eid1) {
		t = t1;
		sid = sid1;
		eid = eid1;
	}
	
	public boolean equals(Order other) {
		return (t==other.t && sid==other.sid && eid==other.eid);
	}
}

class Node {
	public int placeId, orderId;
	
	public Node() {}
	
	public Node(int placeId_, int orderId_) {
		placeId = placeId_;
		orderId = orderId_;
	}
	
	public boolean equals(Node other) {
		return (placeId==other.placeId && orderId==other.placeId);
	}
}

class Hop {
	public double arriveTime, leaveTime;
	public Pnt pos;
	public int buckNum;
	ArrayList<Integer> bucks;
	
	public Hop() {
		bucks = new ArrayList<Integer>();
	}
	
	public Hop(double arrive, double leave, double x1, double y1, int buckNum1) {
		arriveTime = arrive;
		leaveTime = leave;
		pos = new Pnt(x1, y1);
		buckNum = buckNum1;
		bucks = new ArrayList<Integer>();
	}
	
	public void add(int orderId) {
		bucks.add(orderId);
	}
	
	public void clear() {
		bucks.clear();
	}
	
	public void addAll(ArrayList<Integer> bucks_) {
		bucks.clear();
		bucks.addAll(bucks_);
	}
	
	public int size() {
		return bucks.size();
	}
	
	public Integer get(int idx) {
		return bucks.get(idx);
	}
}

class Route {
	public int driverId, hopNum;
	ArrayList<Hop> hops;
	
	public Route() {
		hops = new ArrayList<Hop>();
	}
	
	public Route(int driverId_, int hopNum_) {
		driverId = driverId_;
		hopNum = hopNum_;
	}
	
	public void add(Hop h) {
		hops.add(h);
	}
	
	public Hop get(int idx) {
		return hops.get(idx);
	}
	
	public int size() {
		return hops.size();
	}
}

// ------------- class rideSharingVis itself --------------
public class rideSharingVis {
	final int GRAPH_WIDTH = 100;
	final int GRAPH_HEIGHT = 100;
    public static final double waitTime = 0.0;
    public static final double eps = 1e-4;
    public static final double inf = 1e20;
    public static String networkFileName, routeFileName;
    int NRest, NDist, NOrder, NDriver, CAP;
	Pnt[] rests;
	Pnt[] dists;
	Order[] orders;
	Route[] routes;
    int[] taken;
    double[] deliverTime;
    public static int delay = 100;
    public static boolean startPaused = true;
    ArrayList<Pnt> progress = new ArrayList<Pnt>();
    final Object worldLock = new Object();
    SecureRandom rnd = null;
	double totTime, stuResult;
	
	// ---------------------------------------------------
	void readNetwork(String fileName) {
        if (fileName == null) {
            addFatalError("networkFileName is invalid");
            System.exit(1);
        }
		MyFileReader in = new MyFileReader(fileName);
		
		// constant variable
		NRest = in.nextInt();
		NDist = in.nextInt();
		NDriver = in.nextInt();
		CAP = in.nextInt();
		NOrder = in.nextInt();
		
		// init array
		rests = new Pnt[NRest];
		dists = new Pnt[NDist];
		routes = new Route[NDriver];
		orders = new Order[NOrder];
        taken = new int[NOrder];
        deliverTime = new double[NOrder];
        Arrays.fill(taken, -1);
        Arrays.fill(deliverTime, inf);
		
		// read array
		double x, y;
		for (int i=0; i<NRest; ++i) {
			x = in.nextDouble();
			y = in.nextDouble();
			rests[i] = new Pnt(x, y);
		}
		
		for (int i=0; i<NDist; ++i) {
			x = in.nextDouble();
			y = in.nextDouble();
			dists[i] = new Pnt(x, y);
		}
		
		double t;
		int sid, eid;
		for (int i=0; i<NOrder; ++i) {
			t = in.nextDouble();
			sid = in.nextInt();
			eid = in.nextInt();
			orders[i] = new Order(t, sid, eid);
		}
	}
	
	// ---------------------------------------------------
	void readRoute(String fileName) {
        if (fileName == null) {
            addFatalError("routeFileName is invalid");
            System.exit(1);
        }
		MyFileReader in = new MyFileReader(fileName);
		int driverId, hopNum;
		double arriveTime, leaveTime, x, y;
		int buckNum, orderId;
		
		for (int i=0; i<NDriver; ++i) {
			driverId = in.nextInt();
			hopNum = in.nextInt();
			routes[i] = new Route(driverId, hopNum);
			for (int j=0; j<hopNum; ++j) {
				x = in.nextDouble();
				y = in.nextDouble();
				arriveTime = in.nextDouble();
				leaveTime = in.nextDouble();
				buckNum = in.nextInt();
				Hop hop = new Hop(arriveTime, leaveTime, x, y, buckNum);
				for (int k=0; k<buckNum; ++k) {
					orderId = in.nextInt();
					hop.add(orderId);
				}
				routes[i].add(hop);
			}
		}

        stuResult = in.nextDouble();
	}

    double Length(Pnt a, Pnt b) {
        return Math.sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
    }

    private int dcmp(double x) {
        if (Math.abs(x) < eps)
            return 0;
        return x>0 ? 1 : -1;
    }

    TreeSet<Integer> getOrderSet(Hop hop) {
        return new TreeSet<Integer>(hop.bucks);
    }

    int getRestId(Pnt p) {
        for (int i=0; i<NRest; ++i)
            if (rests[i].equals(p))
                return i;
        return -1;
    }

    int getDistId(Pnt p) {
        for (int i=0; i<NDist; ++i)
            if (dists[i].equals(p))
                return i;
        return -1;
    }
	
    // ---------------------------------------------------
    void generate(String seed) {
        try {
            /*dp nothing*/
        } catch (Exception e) {
            addFatalError("An exception occurred while generating test case.");
            e.printStackTrace(); 
        }
    }

    // ---------------------------------------------------
    boolean judgeHop(Hop preHop, Hop curHop) {
        if (curHop.buckNum > CAP) return false;

        double simArrive = preHop.leaveTime + Length(preHop.pos, curHop.pos);
        double simLeave = simArrive;

        if (dcmp(curHop.arriveTime - curHop.leaveTime) > 0)
            return false;
        if (dcmp(simArrive - curHop.arriveTime) > 0)
            return false;
        if (dcmp(simLeave - curHop.arriveTime) < 0)
            return false;

        Pnt curPos = curHop.pos;
        TreeSet<Integer> preSet = getOrderSet(preHop);
        TreeSet<Integer> curSet = getOrderSet(curHop);

        Iterator<Integer> iter;
        Integer orderId;

        // Iterate preSet;
        iter = preSet.iterator();
        while (iter.hasNext()) {
            orderId = iter.next();
            if (!curSet.contains(orderId)) {
                // this order should be droped off here
                if (!curPos.equals(dists[orders[orderId].eid]))
                    return false;
                if (taken[orderId] != 0) return false;
                taken[orderId] = 1;
                deliverTime[orderId] = curHop.arriveTime;
            }
        }

        // Iterate curSet;
        iter = curSet.iterator();
        while (iter.hasNext()) {
            orderId = iter.next();
            if (!preSet.contains(orderId)) {
                if (!curPos.equals(rests[orders[orderId].sid]))
                    return false;
                if (taken[orderId] != -1) return false;
                taken[orderId] = 0;

                simLeave = Math.max(simLeave, orders[orderId].t+waitTime);
            }
        }

        if (dcmp(curHop.leaveTime-simLeave) < 0)
            return false;

        return true;
    }

    void updateHop(Hop hop) {
        progress.add(hop.pos);
    }

    double calcResult() {
        double ret = 0.0;

        for (int i=0; i<NOrder; ++i) {
            if (taken[i] != -1) return -1.0;
            ret = Math.max(ret, deliverTime[i]-orders[i].t);
        }
        
        return ret;
    }

    // ---------------------------------------------------
    public double runTest(String seed) {
        try {
            generate(seed);
            {
                double begTime = System.currentTimeMillis();
                double endTime = System.currentTimeMillis();    
            }

            readNetwork(networkFileName);

            if (vis) {
                // draw the image
                jf.setSize(GRAPH_WIDTH, GRAPH_HEIGHT);
                jf.setVisible(true);
                draw();
                if (startPaused)
                {
                    v.pauseMode = true;
                }
                v.processPause();
            }

            if (exec != null) {
                try {
                    Runtime rt = Runtime.getRuntime();
                    String cmdLine = exec + " " + networkFileName + " " + routeFileName;
                    proc = rt.exec(cmdLine);
                    //os = proc.getOutputStream();
                    //is = proc.getInputStream();
                    //br = new BufferedReader(new InputStreamReader(is));
                    new ErrorReader(proc.getErrorStream()).start();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }

            synchronized (worldLock) {
                readRoute(routeFileName);
            }

            for (int i=0; i<NDriver; ++i) {
                int hopNum = routes[i].hopNum;
                if (hopNum == 0) continue;
                Hop preHop = routes[i].get(0), curHop;
                synchronized (worldLock) {
                    updateHop(preHop);
                }
                for (int j=1; j<hopNum; ++j) {
                    curHop = routes[i].get(j);
                    if (!judgeHop(preHop, curHop)) {
                        addFatalError("Route of Driver_" + i + "at step_" + j + " is invalid.");
                        endTest();
                        return -1.0;
                    }

                    // update route
                    synchronized (worldLock) {
                        updateHop(curHop);
                    }
                    preHop = curHop;
                }
                if (preHop.buckNum != 0)
                    return -1.0;
            }
            
            if (vis) {
                // update vis
                draw();
                v.processPause();
                try {
                    Thread.sleep(delay);
                } catch (Exception e) {
                    // do nothing
                }
            }

            double simResult = calcResult();
            if (dcmp(simResult - stuResult) != 0)
            	return -1.0;
            else
            	return stuResult;

        } catch (Exception e) { 
            addFatalError("An exception occurred while trying to process your program's results.");
            e.printStackTrace(); 
            return -1.0;
        }
    }

    void endTest() {

    }
    
// ------------- visualization part ----------------------
    static String exec;
    static boolean vis;
    static Process proc;
    static String saveFile = null;
    JFrame jf;
    Vis v;
    InputStream is;
    OutputStream os;
    BufferedReader br;
    // problem-specific drawing params
    final int SZX = GRAPH_WIDTH+2, SZY=GRAPH_HEIGHT+2;
    volatile boolean ready;
    volatile int Ncur;
    volatile int[] Pcur;
    
    // ---------------------------------------------------
    void draw() {
        if (!vis) return;
        v.repaint();
    }
    // ---------------------------------------------------
    BufferedImage drawRoute() {
        BufferedImage bi = new BufferedImage(SZX+10,SZY+10, BufferedImage.TYPE_INT_RGB);
        Graphics2D g2 = (Graphics2D)bi.getGraphics();
        synchronized (worldLock)
        {
            //background
            g2.setColor(new Color(0xD3D3D3));
            g2.fillRect(0,0,SZX+10,SZY+10);
            g2.setColor(Color.BLACK);
            g2.fillRect(0,0,GRAPH_WIDTH+2,GRAPH_HEIGHT+2);
            //frame
            g2.setColor(Color.WHITE);
            g2.drawRect(0,0,GRAPH_WIDTH+2,GRAPH_HEIGHT+2);

            // draw paths
            if (!progress.isEmpty()) {
                int sz = progress.size();
                Pnt pre = progress.get(0), cur;
                for (int i=1; i<sz; ++i)
                {
                    cur = progress.get(i);
                    g2.setColor(Color.GREEN);
                    g2.drawLine((int)pre.x, (int)pre.y, (int)cur.x, (int)cur.y);
                }
            }
            // draw rests
            for (int i=0; i<NRest; ++i) {
                g2.setColor(Color.BLUE);
                g2.fillRect((int)rests[i].x-2, (int)rests[i].y-2, 4, 4);
            }
            // draw dists
            for (int i=0; i<NDist; ++i) {
                g2.setColor(Color.BLUE);
                g2.fillOval((int)dists[i].x-2, (int)dists[i].y-2, 4, 4);
            }
            
        }
        return bi;
    }
    // ---------------------------------------------------
    void saveRoute(String filename)
    {
        try {
            BufferedImage bi = drawRoute();
            File outputfile = new File(filename);
            ImageIO.write(bi, "png", outputfile);
        } catch (IOException e) {
            addFatalError("An exception occurred while trying to save the image.");
            e.printStackTrace();
        }
    }
    // ---------------------------------------------------
    public class Vis extends JPanel implements WindowListener {
        final Object keyMutex = new Object();
        boolean keyPressed;
        public boolean pauseMode = false;

        class DrawerKeyListener extends KeyAdapter {
            public void keyPressed(KeyEvent e) {
                synchronized (keyMutex) {
                    if (e.getKeyChar() == ' ') {
                        pauseMode = !pauseMode;
                    }
                    keyPressed = true;
                    keyMutex.notifyAll();
                }
            }
        }

        public void paint(Graphics g)
        {
          try {
            BufferedImage bi = drawRoute();
            g.drawImage(bi,0,0,SZX+10,SZY+10,null);
          }
          catch (Exception e) { e.printStackTrace(); }
        }

        public Vis()
        {
            jf.addWindowListener(this);
            jf.addKeyListener(new DrawerKeyListener());
        }

        public void processPause() {
            synchronized (keyMutex)
            {
                if (!pauseMode) {
                    return;
                }
                keyPressed = false;
                while (!keyPressed) {
                    try {
                        keyMutex.wait();
                    } catch (InterruptedException e) {
                        // do nothing
                    }
                }
            }
        }

    // ---------------------------------------------------
        //WindowListener
        public void windowClosing(WindowEvent e) { 
            if(proc != null)
                try { proc.destroy(); } 
                catch (Exception ex) { ex.printStackTrace(); }
            System.exit(0); 
        }
        public void windowActivated(WindowEvent e) { }
        public void windowDeactivated(WindowEvent e) { }
        public void windowOpened(WindowEvent e) { }
        public void windowClosed(WindowEvent e) { }
        public void windowIconified(WindowEvent e) { }
        public void windowDeiconified(WindowEvent e) { }
    }
    // ---------------------------------------------------
    public rideSharingVis(String seed) {
        totTime = 0.0;
        //interface for runTest
        if (vis)
        {
            jf = new JFrame();
            v = new Vis();
            jf.getContentPane().add(v);
        }
        double ans = runTest(seed);
        System.out.println("Score = " + ans + ", time = " + totTime + "ms.");
        if (proc != null) {
            try { 
                proc.destroy(); 
            } catch (Exception e) { 
                e.printStackTrace(); 
            }
        }
    }
    // ---------------------------------------------------
    public static void main(String[] args) {
        String seed = "1";
        vis = false;
        for (int i = 0; i<args.length; i++)
        {
            if (args[i].equals("-seed"))
                seed = args[++i];
            if (args[i].equals("-exec"))
                exec = args[++i];
            if (args[i].equals("-save"))
                saveFile = args[++i];
            if (args[i].equals("-vis"))
                vis = true;
            if (args[i].equals("-delay"))
                delay = Integer.parseInt(args[++i]);
            if (args[i].equals("-network"))
                networkFileName = args[++i];
			if (args[i].equals("-route"))
				routeFileName = args[++i];
        }
        rideSharingVis f = new rideSharingVis(seed);
    }

    // ---------------------------------------------------
    void addFatalError(String message) {
        System.out.println(message);
        System.out.flush();
    }
}

class ErrorReader extends Thread{
    InputStream error;
    public ErrorReader(InputStream is) {
        error = is;
    }
    public void run() {
        try {
            byte[] ch = new byte[50000];
            int read;
            while ((read = error.read(ch)) > 0)
            {   String s = new String(ch,0,read);
                System.out.print(s);
                System.out.flush();
            }
        } catch(Exception e) { }
    }
}

class MyFileReader {
	private BufferedReader reader;
	private StringTokenizer tokenizer;
	
	public MyFileReader(String fileName) {
		try {
			reader = new BufferedReader(new FileReader(fileName));
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
		tokenizer = null;
	}
	
	public String next() {
		while (tokenizer==null || !tokenizer.hasMoreTokens()) {
			try {
				tokenizer = new StringTokenizer(reader.readLine());
			} catch (IOException e) {
				throw new RuntimeException(e);
			}
		}
		return tokenizer.nextToken();
	}
	
	public double nextDouble() {
		return Double.parseDouble(next());
	}
	
	public int nextInt() {
		return Integer.parseInt(next());
	}
	
	public long nextLong() {
		return Long.parseLong(next());
	}
}