import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;

public class P1620 {
    public static void main(String... args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(br.readLine());
        Map<String, Integer> map = new HashMap<>();
        List<String> list = new ArrayList<>();

        int N = Integer.parseInt(st.nextToken());
        int M = Integer.parseInt(st.nextToken());

        for (int i = 0; i < N; i++) {
            String s = br.readLine();
            map.put(s, i + 1);
            list.add(s);
        }

        for (int i = 0; i < M; i++) {
            String cur = br.readLine();
            if (map.containsKey(cur)) {
                System.out.println(map.get(cur));
            } else {
                int index = Integer.parseInt(cur);
                System.out.println(list.get(index - 1));
            }
        }
    }
}
