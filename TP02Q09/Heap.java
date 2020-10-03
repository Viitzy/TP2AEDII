public static class Heap{

private Jogador[] vet_heap;
private int tam = 0;

private void swap(Jogador vet[], int pos1, int pos2){
	int aux = vet[pos2];
	vet[pos2] = vet[pos1];
	vet[pos1] = aux;
}

private void add_to_heap(Jogador x){
    int pos_x = tam;
    vet_heap[tam] = x;
    tam++;
	while(pos_x > 0){
		if(vet_heap[(pos_x-1)/2].getAltura() < vet_heap[pos_x].getAltura()){
			swap(vet_heap, (pos_x-1)/2, pos_x);
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
	
	while(i < ((vet.length-1)/2)){
		if(vet_heap[i].getAltura() < vet_heap[2*i+1].getAltura() || vet_heap[i].getAltura() < vet_heap[2*i+2].getAltura()){
			pos = vet_heap[2*i+1].getAltura() > vet_heap[2*i+2].getAltura() ? 2*i+1 : 2*i+2;
			swap(vet_heap, i, pos);
			i = pos;
		}else{
			i+=vet.length;
		}
	}
	return removido;
}

public void sort(Jogador vet[]){
    vet_heap = new Jogador[vet.length];

    for(int i = 0; i< vet.length; i++)
        vet_heap[i] = new Jogador();
    
    for(int i = 0; i< vet.length; i++)
        add_to_heap(vet[i]);

    for(int i= vet.length-1; i>=0; i--)
		vet[i] = remove_from_heap();
}


}
