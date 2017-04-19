import java.io.*;
import java.security.*;

public class GraphDrawing {
    public int[] plot(int NV, int[] edges) {
        int[] ret = new int[2 * NV];
        SecureRandom r1;
        try {
           r1 = SecureRandom.getInstance("SHA1PRNG");
        } catch (Exception e) { return ret; }
        r1.setSeed(123);
        for (int i = 0; i < 2 * NV; ++i) {
            ret[i] = r1.nextInt(701);
        }
        return ret;
    }
    // -------8<------- end of solution submitted to the website -------8<-------
    public static void main(String[] args) {
    try {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        int N = Integer.parseInt(br.readLine());
        int E = Integer.parseInt(br.readLine());
        int[] edges = new int[E];
        for (int i = 0; i < E; ++i) {
            edges[i] = Integer.parseInt(br.readLine());
        }

        GraphDrawing gd = new GraphDrawing();
        int[] ret = gd.plot(N, edges);

        System.out.println(ret.length);
        for (int i = 0; i < ret.length; ++i) {
            System.out.println(ret[i]);
        }
    }
    catch (Exception e) {}
    }
}

