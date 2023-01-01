char map[13][33] = {
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",
	"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"};
	
char player = '@';
int px = 1;
int py = 1;


int xorshift(int i);
int bk =0;//seed work


void add_player(){

	map[py][px] = player;
}
int xorshift(int i){
			

			 int bpa = i;
			 bpa =  bpa ^ (bpa << 13); 
			 bpa = bpa ^ (bpa >> 17);
			 bpa = bpa ^ (bpa << 5);
			 bpa = bpa & 65535;
			 
			 return bpa;

}

void maze_gen(int seed_a){
	int seed = seed_a;
	for(int k =2; k<9;k++){
		for(int i = 1; i< 31;i++){
			seed = xorshift(seed);
			if(seed%2 == 1){
				map[k+1][i] = ' ';
			}else{
				map[k-1][i] = ' ';
			}
		}
	}
}

void boss_gen(){
	maze_gen(0);
	
}



int stage_num =0;
char stage[7][19] = {"Arlong park","Alabasta","Skypiea","Water-7","Enies Lobby"};
const char * stage_tile = "W.#G";

void map_reset(){
	for(int i =0; i<11;i++){
		for(int k =0; k<32;k++){
			map[i][k] = stage_tile[stage_num];
		}
	}

}



void disp_map(){
	maze_gen(bk);
	bk = xorshift(++bk);
	maze_gen(bk);
	bk = xorshift(++bk);	
	add_player();
	print_string("EchOS-");
	print_string("Current_Stage: ");
	print_string(stage[stage_num]);
	print_string("\n\n");
	

	for(int i =0; i<11;i++){
		print_string((char*)&map[i]);
		print_string("\n");
	}
	map_reset();
}