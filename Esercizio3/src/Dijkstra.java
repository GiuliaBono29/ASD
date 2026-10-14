import java.util.ArrayList;
import java.util.Hashtable;

public class Dijkstra<N extends Comparable<N>, A extends Comparable<A>> {
    Hashtable<String,Double> DISTANCE = null;
    Hashtable<String,String> FATHER = null;

    public  Dijkstra(Graph<String, Double> GRAPH, String ORIGIN, String DESTINATION){
        DISTANCE=new Hashtable<>();
        FATHER=new Hashtable<>();
        this.dijkstra(GRAPH, ORIGIN, DESTINATION);
    }
    
    
    public void dijkstra(Graph<String,Double> GRAPH, String ORIGIN, String DESTINATION){
        String SOURCE=ORIGIN;
        ArrayList<Node<String, Double>> ADJACENCY = GRAPH.returnNodesAdj(SOURCE);
        HeapMinimo<Node<String,Double>> PRECEDENCES = new HeapMinimo<>();
        PRECEDENCES.newHeap();
        initialize(GRAPH, PRECEDENCES, SOURCE);

        while(PRECEDENCES.size()!=0) {
            SOURCE= PRECEDENCES.extract().getElem();
            ADJACENCY = GRAPH.returnNodesAdj(SOURCE);
            modify(SOURCE, ADJACENCY, PRECEDENCES);
        }

        System.out.println("Distanza tra " + ORIGIN + " e " + DESTINATION + " e' di " + DISTANCE.get(DESTINATION) + " m");
    }

    private void modify(String SOURCE, ArrayList<Node<String, Double>> ADJACENCY, HeapMinimo<Node<String, Double>> PRECEDENCES) {
        for (int i = 0; i < ADJACENCY.size(); i++) {
            Double DISTANCE_SOURCE=DISTANCE.get(SOURCE) + ADJACENCY.get(i).getLabel();
            String NAME = ADJACENCY.get(i).getElem();
            if(PRECEDENCES.decrese(new Node<>(NAME, DISTANCE.get(NAME)), new Node<>(NAME, DISTANCE_SOURCE))){
                DISTANCE.replace(NAME, DISTANCE_SOURCE);
                FATHER.replace(NAME, SOURCE);
            }
        }
    }

    private void initialize(Graph<String,Double> GRAPH, HeapMinimo<Node<String, Double>> PRECEDENCES, String SOURCE) {
        for(String CURRENT_NODE : GRAPH.returnNodes()){
            if(CURRENT_NODE.equals(SOURCE) == false){
                PRECEDENCES.insert(new Node<>(CURRENT_NODE, Double.POSITIVE_INFINITY));
                DISTANCE.put(CURRENT_NODE, Double.POSITIVE_INFINITY);
                FATHER.put(CURRENT_NODE, "");
            }
        }

        PRECEDENCES.insert(new Node<>(SOURCE,0.0));
        DISTANCE.put(SOURCE, 0.0);
    }

}
