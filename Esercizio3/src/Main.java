import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class Main {

    public static void main(String[] args) throws Exception {

        Graph GRAPH=null;

        GRAPH = new Graph(true);

        HeapMinimo HEAP = new HeapMinimo();

        file_Open(GRAPH);

        Dijkstra DISTANCE = new Dijkstra<>(GRAPH, "torino", "catania");

    }

    static void file_Open(Graph GRAPH) throws IOException, Exception {

            Path MY_OBJ = Paths.get("C:\\Users\\GiuliaBono\\Desktop\\Algoritmi Finiti\\Esercizio4\\src\\italian_dist_graph.csv");

            BufferedReader FILE_IN = Files.newBufferedReader(MY_OBJ);

            String DATA = null;

            while ((DATA = FILE_IN.readLine()) != null){
                String[] TOKEN = DATA.split(",");

                if(!GRAPH.containNode(TOKEN[0])) {
                    GRAPH.insertNode(TOKEN[0]);
                }
                if(!GRAPH.containNode(TOKEN[1])) {
                    GRAPH.insertNode(TOKEN[1]);
                }
                GRAPH.insertArc(TOKEN[0], TOKEN[1], Double.parseDouble(TOKEN[2]));
                GRAPH.insertArc(TOKEN[1], TOKEN[0], Double.parseDouble(TOKEN[2]));
            }
    }
}