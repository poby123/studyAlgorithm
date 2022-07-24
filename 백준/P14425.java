import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;

public class P14425 {
    private static int N, M, ans;
    private static Set<String> S = new HashSet<>();
    private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

    static int check(String target) {
        if (S.contains(target)) {
            return 1;
        }
        return 0;
    }

    static void solve() throws Exception {
        StringTokenizer st = new StringTokenizer(br.readLine());
        N = Integer.parseInt(st.nextToken());
        M = Integer.parseInt(st.nextToken());

        for (int i = 0; i < N; i++) {
            S.add(br.readLine());
        }

        for (int i = 0; i < M; i++) {
            ans += check(br.readLine());
        }

        System.out.println(ans);
    }

    public static void main(String... args) throws Exception {
        solve();
    }
}