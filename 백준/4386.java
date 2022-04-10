// https://www.acmicpc.net/problem/4386

import java.io.*;
import java.util.*;

public class Main
{
    static int[] parent = new int[101];
    
    static class Star{
        static int number;
        double x, y;
        int n;
        
        Star(double x, double y){
            this.x = x;
            this.y = y;
            this.n = ++number;
        }
    }
    
    static class Edge implements Comparable<Edge>{
        Star a, b;
        double cost;
        
        Edge(Star a, Star b, double cost){
            this.a = a;
            this.b = b;
            this.cost = cost;
        }
        
        @Override
        public int compareTo(Edge e){
            if(this.cost == e.cost){
                return 0;
            }
            else if(this.cost < e.cost){
                return -1;
            }
            else{
                return 1;
            }
        }
    }

    
    static double getDistance(Star a, Star b){
        return Math.sqrt(Math.pow(a.x - b.x, 2) + Math.pow(a.y - b.y, 2)); 
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
    
    static double kruskal(List<Edge> G){
        double ans = 0;
        
        for(Edge e: G){
            Star a = e.a;
            Star b = e.b;
            double cost = e.cost;
            
            if(find(a.n) != find(b.n)){
                union(a.n, b.n);
                ans += cost;        
            }
        }
        
        return ans;
    }
    
    static void solve() throws Exception{
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        List<Star> stars = new ArrayList<>();
        
        for(int i=1;i<=100;i++){
            parent[i] = i;
        }
        
        // inputs
        int N = Integer.parseInt(br.readLine());
        List<Edge> G = new ArrayList<>();
        
        for(int i=0;i<N;i++){
            StringTokenizer st = new StringTokenizer(br.readLine());
            double x = Double.parseDouble(st.nextToken());
            double y = Double.parseDouble(st.nextToken());
            
            stars.add(new Star(x, y));
        }
        
        // make graph
        for(int i=0;i<N-1;i++){
            for(int j=i+1;j<N;j++){
                double c = getDistance(stars.get(i), stars.get(j));
                G.add(new Edge(stars.get(i), stars.get(j), c));
            }
        }
        
        Collections.sort(G);
        System.out.println(kruskal(G));
    }
    
    public static void main(String[] args) throws Exception{
        Main.solve();
    }
}
