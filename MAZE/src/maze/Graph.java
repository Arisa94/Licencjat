package maze;

public class Graph{
    
    int h;
    int w;
    Node[][] nodes;
    
    public Graph(int passedH, int passedW){
        
        h = passedH;
        w = passedW;
        
    }
    
    public void fillGraph(){
        
        for(int i = 0; i < w; i++){
            
            for(int j = 0; j < h; j++){
                
                nodes[i][j] = new Node(j + (i * h)); // exclusive indexes of group for each node. Filling up to down from the left column
                
            }
        }
        
    }
}
