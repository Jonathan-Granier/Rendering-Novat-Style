/*Test d'indexation d'un OBJ*/


struct Index{
	int position;
	int normal;
	int texCoord;
	
	int indice;
}


std::vector<Index> indexVertex;
//Remplissage par la lecture

for(i=0;i<indexVertex.size();i++)
{
	if(indexVertex[i]==-1){
		for(j=i+1;j<indexVertex.size();j++){
		if(indexVertex[i] == indexVertex[j])
			indexVertex[j].indice = i;
		}
	}
}


std::vector<unsigned int> indices;

for(i=0;i<indexVertex.size();i++){
	if(indexVertex.indice == -1){
		//pushback Vertex
		indices.pushback(i);
	}
	else
	{
		indices.pushback(indexVertex[i].indice);
	}
}

