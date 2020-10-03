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
        Arq.openWrite("677213_countingsort.txt");

        Arq.print("677213"+'\t'+tempo+'\t'+comp);

        Arq.close();
    }

    public static int getMaior(Jogador[] array) {
        int maior = array[0].getAltura();
 
         for (int i = 0; i < array.length; i++) {
          if(maior < array[i].getAltura()){
             maior = array[i].getAltura();
          }
         }
        return maior;	
     }

    public static Jogador[] sort(Jogador[] array) {
        int n = array.length;
        int comparacoes = array.length;
        long tempoinicio = System.currentTimeMillis();

        //Array para contar o numero de ocorrencias de cada elemento
        int[] count = new int[getMaior(array) + 1];
        Jogador[] ordenado = new Jogador[n];
        
        //Instancia os vetores de Jogador como objetos
        for(int i = 0; i< n ; i++)
            ordenado[i] = new Jogador();

        //Inicializar cada posicao do array de contagem 
          for (int i = 0; i < count.length; count[i] = 0, i++);
  
        //Agora, o count[i] contem o numero de elemento iguais a i
        for (int i = 0; i < n; count[array[i].getAltura()]++, i++);
  
        //Agora, o count[i] contem o numero de elemento menores ou iguais a i
        for(int i = 1; i < count.length; count[i] += count[i-1], i++);
  
        //Ordenando
        for(int i = n-1; i >= 0; ordenado[count[array[i].getAltura()]-1] = array[i], count[array[i].getAltura()]--, i--);
  
        //Copiando para o array original
        for(int i = 0; i < n; array[i] = ordenado[i], i++);

        long tempo = System.currentTimeMillis() - tempoinicio;

        log(comparacoes , tempo);

        return array;
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
    
    jogador = sort(jogador);

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