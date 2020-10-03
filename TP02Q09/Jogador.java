class Jogador{
    private int id, altura, peso, anoNascimento;
    private String nome, universidade, cidadeNascimento, estadoNascimento;
    
    public static boolean isFim(String s){
        return(s.length()>= 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M');
    }

    public Jogador(){
        this.id = 0;
        this.altura = 0;
        this.peso = 0;
        this.anoNascimento = 0;
        this.nome = "";
        this.universidade = "";
        this.cidadeNascimento = "";
        this.estadoNascimento = "" ;   
    } 
    
    public Jogador(int id, int altura, int peso, int anoNascimento, String nome, String universidade, String cidadeNascimento, String estadoNascimento){
        this.id = id;
        this.altura = altura;
        this.peso = peso;
        this.anoNascimento = anoNascimento;
        this.nome = nome;
        this.universidade = universidade;
        this.cidadeNascimento = cidadeNascimento;
        this.estadoNascimento = estadoNascimento;  
    }

    public void setId(int id){
        this.id = id;
    }

    public int getId(){
        return this.id;
    }

    public void setAltura(int altura){
        this.altura = altura;
    }

    public int getAltura(){
        return this.altura;
    }

    public void setPeso(int peso){
        this.peso = peso;
    }

    public int getPeso(){
        return this.peso;
    }

    public void setAnoNascimento(int anoNascimento){
        this.anoNascimento = anoNascimento;
    }

    public int getAnoNascimento(){
        return this.anoNascimento;
    }

    public void setNome(String nome){
        this.nome = nome;
    }

    public String getNome(){
        return this.nome;
    }

    public void setUniversidade(String universidade){
        this.universidade = universidade;
    }

    public String getUniversidade(){
        return this.universidade;
    }

    public void setCidadeNascimento(String cidadeNascimento){
        this.cidadeNascimento = cidadeNascimento;
    }

    public String getCidadeNascimento(){
        return this.cidadeNascimento;
    }

    public void setEstadoNascimento(String estadoNascimento){
        this.estadoNascimento = estadoNascimento;
    }

    public String getEstadoNascimento(){
        return this.estadoNascimento;
    }

    public Jogador clone(){
        return new Jogador(this.id, this.altura, this.peso, this.anoNascimento, this.nome, this.universidade, this.cidadeNascimento, this.estadoNascimento);
    }
    
    public void ler(String s){
        String[] array = s.split(",");   

        this.id = Integer.parseInt(array[0]);
        this.nome = array[1];
        this.altura = Integer.parseInt(array[2]);
        this.peso = Integer.parseInt(array[3]);
            if(array[4].length() == 0)
                this.universidade = "nao informado";
            else
                this.universidade = array[4];
        this.anoNascimento = Integer.parseInt(array[5]);
            if(array.length == 8){
                this.cidadeNascimento = array[6];
                this.estadoNascimento = array[7];
            }
            else{
                this.cidadeNascimento = "nao informado";
                this.estadoNascimento = "nao informado";
            }  
    }

    public void imprimir(){
        System.out.println("["+getId()+" ## "+getNome()+" ## "+getAltura()+" ## "+getPeso()+" ## "+getAnoNascimento()+" ## "+getUniversidade()+" ## "+getCidadeNascimento()+" ## "+getEstadoNascimento()+"]");
    }

    public static void log(int comp , long tempo){
        Arq.openWrite("677213_heapsort.txt");

        Arq.print("677213"+'\t'+tempo+'\t'+comp);

        Arq.close();
    }

public static class Heap{

        private Jogador[] vet_heap;
        private int tam = 0;
        private int comparacoes = 0;

        private void swap(int pos1, int pos2){
            Jogador aux = new Jogador();
            aux = vet_heap[pos2];
            vet_heap[pos2] = vet_heap[pos1];
            vet_heap[pos1] = aux;
        }
        
        private void add_to_heap(Jogador x){
            int pos_x = tam;
            vet_heap[tam] = x;
            tam++;
            while(pos_x > 0){
                if(vet_heap[(pos_x-1)/2].getAltura() < vet_heap[pos_x].getAltura()){
                    comparacoes++;
                    swap((pos_x-1)/2, pos_x);
                    pos_x = (pos_x-1)/2;
                }else{
                    pos_x = -1;
                }
            }
        }   
        
        private Jogador remove_from_heap(){
            Jogador removido = vet_heap[0];
            int i = 0;
            int pos;
            vet_heap[0] = vet_heap[--tam];
            
            while(i < ((tam-1)/2)){
                if(vet_heap[i].getAltura() < vet_heap[2*i+1].getAltura() || vet_heap[i].getAltura() < vet_heap[2*i+2].getAltura()){
                    pos = vet_heap[2*i+1].getAltura() > vet_heap[2*i+2].getAltura() ? 2*i+1 : 2*i+2;
                    comparacoes += 2;
                    swap(i, pos);
                    i = pos;
                }else{
                    i+=vet_heap.length;
                }
            }
            return removido;
        }
        
        public Jogador[] sort(Jogador vet[]){
            long tempoinicio = System.currentTimeMillis();
            vet_heap = new Jogador[vet.length];
            Jogador[] retorno = new Jogador[vet.length];
            
            for(int i = 0; i< vet.length; i++){
                vet_heap[i] = new Jogador();
                retorno[i] = new Jogador();
                
            }
            for(int i = 0; i< vet.length; i++)
                add_to_heap(vet[i]);
            
            for(int i= vet.length-1; i>=0; i--)
                retorno[i] = remove_from_heap();

            long tempo = System.currentTimeMillis() - tempoinicio;
            log(comparacoes , tempo);

            return retorno;
        }
  
}
public static void main(String[] args){
    String[] entrada = new String[1000];
    String[] nomes = new String[1000];
    int numEntrada = 0;
    int numNomes = 0;
    

    do{
        entrada[numEntrada] = MyIO.readLine();
    }while(isFim(entrada[numEntrada++]) == false);
    numEntrada--;

    Jogador[] jogador = new Jogador[numEntrada];
    String[] players = new String [5000];

    Arq.openRead("/tmp/players.csv");// /tmp/

    for (int i = 0 ; i<3923; i++){
        players[i]= Arq.readLine();
    } 
    
    Arq.close();

    int x = 0;
    for(int i = 0 ;  i< numEntrada ; i++){
        x = Integer.parseInt(entrada[i]);
        jogador[i] = new Jogador();
        jogador[i].ler(players[x+1]);
        //jogador[i].imprimir();
    }

        Heap heap = new Heap();
        jogador = heap.sort(jogador);

        for (int i = (numEntrada - 1); i > 0; i--) {
            for (int j = 0; j < i; j++) {
                if (jogador[j].getNome().compareTo(jogador[j + 1].getNome()) > 0 && jogador[j].getAltura() == jogador[j + 1].getAltura()) {
                    Jogador aux = jogador[j];
                    jogador[j]=jogador[j+1];
                    jogador[j+1]=aux;
                }
            }
        }

        // Impressao
        for(int i = 0 ;  i< numEntrada ; i++){
           jogador[i].imprimir();
        }
     

    } 
}