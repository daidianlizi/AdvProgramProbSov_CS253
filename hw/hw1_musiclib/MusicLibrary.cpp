#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "string.h"
#define STRMAX 100
#define SONGMAX 1024
using namespace std;
struct Song {
char title[STRMAX];
char artist[STRMAX];
int year_published;
};

//Singleton
struct MyMusicObject {
	struct Song music_library[SONGMAX];
	int current_number_of_songs;
	char file_name[STRMAX];

	int crunch_down_from_index(int index){
		if (index == SONGMAX -1 ){
			printf("Your MusicLibrary is full, please remove some songs before insert.\n");
			return -1;
		}
		for (int k = current_number_of_songs; k > index; k--){
			music_library[k] = music_library[k-1];
		}
		current_number_of_songs++;
		return 0;
	}
	void crunch_up_from_index(int index){
		for (int k = index; k < current_number_of_songs - 1; k++){
			music_library[k] = music_library[k+1];
		}
		current_number_of_songs--;
	}
	int find_index_of_song_with_name(char* title){
		int l = 0, r = current_number_of_songs - 1;
		//return the literally larger or equal index of the song
		while (l < r){
			int mid = (l+r)>>1;
			(strcmp(title,music_library[mid].title) <= 0)? r = mid : l = mid + 1;
		}
		if (l == current_number_of_songs - 1 && strcmp(title,music_library[l].title) > 0) return current_number_of_songs;
		return l;
	}
	void add_song_to_MusicLibrary(Song song) {
		int i = find_index_of_song_with_name(song.title);
		int flag_crunch_down = crunch_down_from_index(i);
		if (flag_crunch_down == -1 ) return;
		music_library[i] = song;
	}
	bool remove_song_from_MusicLibrary_by_name(char* title){
		int i = find_index_of_song_with_name(title);
		if (i >= current_number_of_songs || strcmp(music_library[i].title,title) != 0){
			return false;
		}
		crunch_up_from_index(i);
		return true;
	}
	bool read_song(FILE* fp){
		Song new_song;
		if (fscanf(fp, "Title: %[^,], Artist: %[^,], Year Published: %d\n", new_song.title, new_song.artist, &new_song.year_published)!= EOF) {
			add_song_to_MusicLibrary(new_song);
			return true;
		} else return false;
	}
	FILE* open_file(const char* filename, bool is_read){
		FILE *fp;
		if (is_read) {//read( check exist before )
			fp = fopen(filename,"r");
			if(fp==NULL){
	  			printf("Your MusicLibrary: %s not found, create this new one for you.\n", filename);
	  		}
  	    }
  	    else {//create new file;
  	    	fp = fopen(filename,"w");
  	    }
  		return fp;
	}
	void print_MusicLibrary(bool line_number){
		if (line_number){
			for (int k = 0; k < current_number_of_songs; k++){
				printf("%d Title: %s, Artist: %s, Year Published: %d\n", k+1, music_library[k].title, music_library[k].artist, music_library[k].year_published);
			}			
		}
		else {
			FILE *fp = open_file(file_name,false);//open the store file;
			for (int k = 0; k < current_number_of_songs; k++){
				fprintf(fp, "Title: %s, Artist: %s, Year Published: %d\n", music_library[k].title, music_library[k].artist, music_library[k].year_published);
			}			
		}
	}
	void load_MusicLibrary(const char* filename){
		strcpy(file_name, filename);
		current_number_of_songs = 0;
		FILE *fp = open_file(filename, true);
		if (fp != NULL) {
		  while (read_song(fp)) ;
		  fclose(fp);
	    }
	    print_MusicLibrary(true);
	}
	void insert_MusicLibrary(){
		Song new_song;
		printf("Title: ");
		scanf("\n%[^\n]",new_song.title);
		printf("Artist: ");
		scanf("\n%[^\n]",new_song.artist);
		printf("Year Published: ");
		scanf("%d", &new_song.year_published);
		add_song_to_MusicLibrary(new_song);
	}
	void delete_MusicLibrary(){
		Song delete_song;
		printf("Title: ");
		scanf("\n%[^\n]",delete_song.title);
		bool exist_found = remove_song_from_MusicLibrary_by_name(delete_song.title);
		if (!exist_found){
			printf("No song name found:%s\n", delete_song.title);
		}
		while ( remove_song_from_MusicLibrary_by_name(delete_song.title) );
	}
	void lookup_MusicLibrary(){
		Song lookup_song;
		printf("Title: ");
		scanf("\n%[^\n]",lookup_song.title);
		int i = find_index_of_song_with_name(lookup_song.title);
		if ( strcmp(music_library[i].title,lookup_song.title) != 0 ){
			printf("No song name found:%s\n", lookup_song.title);
		}
		else{
			printf("Title: %s, Artist: %s, Year Published: %d\n", music_library[i].title, music_library[i].artist, music_library[i].year_published);
		}
	}
	void store_MusicLibrary(){
		print_MusicLibrary(false);
	}	
	char read_command(){
		cout<<"myMuisc Command: ";
		char mycommand;
		while ( true ){
			mycommand = getchar();
			switch (mycommand){
				//Skip any whitespace characters (space, tab, newline).
				case ' ':
				case '\t':
				case '\n':
					continue;
				default:
					break;
			}
			return mycommand;
		}
	}
	void evaluate_command(char cmd){
		switch (cmd){
			case 'I':
			case 'i':
				insert_MusicLibrary();break;
			case 'P':
			case 'p':
				print_MusicLibrary(true);break;
			case 'D':
			case 'd':
				delete_MusicLibrary();break;
			case 'L':
			case 'l':
				lookup_MusicLibrary();break;	
			case 'Q':
			case 'q':			 				 
				store_MusicLibrary(); exit(0); 
			default:
				cout<<"Invalid command character, skipped and ignored.\n";
				break;
		}
	}
} my_music_object;

int main(int argc, char** argv){
	// determine the name of the MusicLibrary file (defaulting to “myMusic”) and load
	if (argc < 2){
		cout<<"You don't give the name to MusicLibrary; we use \"myMusic\" by default.\n";
		my_music_object.load_MusicLibrary("myMusic");
	}
	else {
		my_music_object.load_MusicLibrary(argv[1]);
	}
	//manipulate
	char command;
	while ( true ){
		command = my_music_object.read_command();
		my_music_object.evaluate_command(command);
	}
	return 0;
}