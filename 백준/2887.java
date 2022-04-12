// https://www.acmicpc.net/problem/2887

import java.io.*;
import java.util.*;

public class Main
{
    static int[] parent;
    
    static class Planet {
        static int number;
        int x, y, z;
        int n;
        
        Planet(int x, int y, int z){
            this.x = x;
            this.y = y;
            this.z = z;
            this.n = ++number;
        }
    }
    
    static class Edge implements Comparable<Edge>{
        Planet a, b;
        int cost;
        
        Edge(Planet a, Planet b, int cost){
            this.a = a;
            this.b = b;
            this.cost = cost;
        }
        
        @Override
        public int compareTo(Edge e){
            return cost - e.cost;
        }
    }
    
    
    static int find(int x){
        if(x == parent[x]){
            return x;
        }
        return parent[x] = find(parent[x]);
    }
    
    static void union(int a, int b){
        a = find(a);
        b = find(b);
        
        if(a < b){
            parent[b] = a;
        }
        else{
            parent[a] = b;
        }
    }
    
    static int kruskal(List<Edge> G){
        int ans = 0;
        
        for(Edge e: G){
            Planet a = e.a;
            Planet b = e.b;
            int cost = e.cost;
            
            if(find(a.n) != find(b.n)){
                union(a.n, b.n);
                ans += cost;        
            }
        }
        
        return ans;
    }
    
    static void solve() throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        List<Planet> planets = new ArrayList<>();
        
        // inputs
        int N = Integer.parseInt(br.readLine());
        List<Edge> G = new ArrayList<>();
        
        parent = new int[N+1];
        for(int i=1;i<=N;i++){
            parent[i] = i;
        }
        
        for(int i=0;i<N;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            int x = Integer.parseInt(st.nextToken());
            int y = Integer.parseInt(st.nextToken());
            int z = Integer.parseInt(st.nextToken());
            planets.add(new Planet(x, y, z));
        }
        
        Collections.sort(planets, (a, b)-> a.x - b.x);
        for(int i=0;i<N-1;i++){
            G.add(new Edge(planets.get(i), planets.get(i+1), Math.abs(planets.get(i).x - planets.get(i+1).x)));
        }
        
        Collections.sort(planets, (a, b)-> a.y - b.y);
        for(int i=0;i<N-1;i++){
            G.add(new Edge(planets.get(i), planets.get(i+1), Math.abs(planets.get(i).y - planets.get(i+1).y)));
        }
        
        Collections.sort(planets, (a, b)-> a.z - b.z);
        for(int i=0;i<N-1;i++){
            G.add(new Edge(planets.get(i), planets.get(i+1), Math.abs(planets.get(i).z - planets.get(i+1).z)));
        }
        
        Collections.sort(G);
        System.out.println(kruskal(G));
    }
    
    public static void main(String[] args) throws Exception{
        Main.solve();
    }
}
