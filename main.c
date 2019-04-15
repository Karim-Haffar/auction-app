#include <gtk/gtk.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<signal.h>
//thread bibiotheque
#include<pthread.h>

pthread_t client[10],systems;

int sockfd, new_socket,new_fd1; // listen on sock_fd, new connection on new_fd
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr,their_addr1; // connector's address information
socklen_t sin_size,sin_size1;
struct sigaction sa;
int yes=1;
char s[INET6_ADDRSTRLEN],nombre[10];
int rv;



#define PORT "3490" // the port users will be connecting to
#define BACKLOG 2// how many pending connections queue will hold

int fds[2];
char prix[10];
int prie=100;
char buffer[255];
int n,i=0,k;
GtkWidget *text_view;
GtkTextBuffer *Buffer;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;





typedef struct
{     int id;
	char nature[20];
	char model[20];
	int  quantite ;
        int prix;

}produit;

produit e;
FILE *f;

typedef struct
{
        GSList *windows;
        

} MyApp;


void on_window_destroy (GtkWidget *widget, MyApp *app)
{
        app->windows = g_slist_remove (app->windows, widget);
        
        if (g_slist_length (app->windows) == 0)
        {
                /* last window was closed... exit */
                
                g_debug ("Exiting...");
                g_slist_free (app->windows);
                gtk_main_quit ();
        }
}





/**********temp plus***************************************/

static gboolean on_timeout (gpointer user_data)
{
  static unsigned f_times = 0;

  /*GtkLabel *label = GTK_LABEL (user_data);

  ++f_times;
  gchar *text = g_strdup_printf ("I have been updated %u times", f_times);
  gtk_label_set_label (label, text);
  g_free (text);*/

  return G_SOURCE_CONTINUE; /* or G_SOURCE_REMOVE when you want to stop */
}








/*************saisie**buffer**************************************************************/

void saisie_buffer(int code,int num,int prie)
{
   GtkTextBuffer * p_buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
   //const gchar    * str   = gtk_entry_get_text (GTK_ENTRY (p_entry));
static char donner[1000] ;
       char client[100];
char numero[10];
char prix[10];

if(code==1){

sprintf(client,"%s","\n  client ");
strcat(donner,client);
sprintf(numero,"%d",num);
sprintf(prix,"%d",prie);
strcat(donner,numero);
strcat(donner," : ");
strcat(donner,prix);
 gtk_text_buffer_set_text (p_buf,donner, -1);

}

else
   if(code==2){
sprintf(client,"%s","\n \n the participant number");
strcat(donner,client);
sprintf(numero,"%d",num);
sprintf(prix,"%d",prie);
strcat(donner,numero);
strcat(donner," wined the auction");
//strcat(donner,prix);
 gtk_text_buffer_set_text (p_buf,donner, -1);

}


else if(code==0)
gtk_text_buffer_set_text (p_buf,"Waiting for connection ...", -1);


}


/*/static void saisie_serveur(char[] donner,int i,int num)
{
   GtkTextBuffer * p_buf = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));
   //const gchar    * str   = gtk_entry_get_text (GTK_ENTRY (p_entry));





   gtk_text_buffer_set_text (p_buf,donner, -1);


}

*/





//****************************************************************************************/



/***********************************************************SOCKET***********************************************************************/

 void sigchld_handler(int s)
  {
// waitpid() might overwrite errno, so we save and restore it:
int saved_errno = errno;
while(waitpid(-1, NULL, WNOHANG) > 0);
errno = saved_errno;
  }



 void *client_connect_to_server( void *argument)
{

int n,num;
int new_socket=*((int*)argument);


num=i;
k=i;  



while(1){

       if(i<3)
      n =send(new_socket,"attender l'entrer des participants",255,0);
      
          else
        n =send(new_socket,"attendez votre tour !!",255,0); 

       
             pthread_mutex_lock (&mutex);
            


              while(1)
                {if(i>2)
                   break;
                 }




            if(k==1)
        { n =send(new_socket,"-1",255,0);  
           printf("le Client %d apris l'enchere avec un prix egal a   %d\n",num,prie);
          saisie_buffer(2, num,prie);
        pthread_mutex_unlock (&mutex);
         break;}

              
          sprintf(prix, "%d", prie);
             
           n =send(new_socket,prix,255,0);

           bzero(buffer,256);

           n = recv(new_socket,buffer,255,0);
      
              
            if(0 ==atoi(buffer)){
              bzero(buffer,256);
             n =send(new_socket,"-2",255,0);
               
                k--;
          pthread_mutex_unlock (&mutex);
           close(new_socket);
             break;
                 } 
           
           prie=prie+atoi(buffer);
                
           printf("Client %d : %d\n",num,prie);
             saisie_buffer(1, num,prie);
          pthread_mutex_unlock (&mutex);

     sleep(1);
 }


}








                      /*******server******************/
void server()
{


/**********/

gchar buf[1024];
   gint chars_read;
   GtkTextIter iter;
   chars_read = 1024;
   

/***************/




/*******************************************************************************************SOCKET*******************************/





//declare thread
pthread_t client[10];

int sockfd, new_socket,new_fd1; // listen on sock_fd, new connection on new_fd
struct addrinfo hints, *servinfo, *p;
struct sockaddr_storage their_addr,their_addr1; // connector's address information
socklen_t sin_size,sin_size1;
struct sigaction sa;
int yes=1;
char s[INET6_ADDRSTRLEN];
int rv;


memset(&hints, 0, sizeof hints);//Zero the whole structure before use with memset()

hints.ai_family = AF_UNSPEC;  // AF_INET designe IPV4 &&AF_UNSPEC for both "IPV4 ,IPV6"
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE; // use my IP-> if i use AI_PASSIVE the node name wil be "NULL" && INADDR_ANY=IPV4


if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {// NULL -> is the node name && return information on a particular host name

fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));// gestion des erreurs
//return 1;
}




// loop through all the results and bind to the first we can
for(p = servinfo; p != NULL; p = p->ai_next) {

if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
perror("server: socket");
continue;
}


if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
close(sockfd);
perror("server: bind");
continue;
}


break;
}

freeaddrinfo(servinfo); // all done with this structure

if (p == NULL) {
fprintf(stderr, "server: failed to bind\n");
exit(1);
}



printf("server: waiting for connections...\n");

//saisie_buffer("server: waiting for connections...\n");
/*gtk_text_buffer_get_end_iter(Buffer, &iter);
   while (chars_read == 1024){
     chars_read = read(fds[0], buf, 1024);
     // fprintf(stderr, "%i chars: %s\n", chars_read, buf);
     gtk_text_buffer_insert (Buffer, &iter, buf, chars_read);}*/

//saisie_buffer("server: waiting for connections...\n");

if (listen(sockfd, BACKLOG) == -1) {  // listen
perror("listen");
//exit(1);
}





if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
       // return 1; 
    } 

int tab[255];
int resultat;
int j=0;


 while(1)
     {
        sin_size = sizeof their_addr;
     new_socket = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

if(new_socket<0)
 printf("erreur de creation du socket\n");



if(pthread_create(&client[i],NULL,(void*)client_connect_to_server,&new_socket) != 0)
close(sockfd);


 
i++;


}
 close(new_socket);

}








/****************************************************************************************SOCKET*******************************/













/***********************************************************SOCKET***********************************************************************/

void *auction()
{
while(1)
    {
        sin_size = sizeof their_addr;
     new_socket = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

if(new_socket<0)
 printf("erreur de creation du socket\n");



if(pthread_create(&client[i],NULL,(void*)client_connect_to_server,&new_socket) != 0)
close(sockfd);


 
i++;
sprintf(nombre,"%d",i);

}
 close(new_socket);

}

void set_nb_participant(GtkWidget *label1r)
{



}



void interface_enchere(GtkWidget *widget, MyApp *app)
{

gchar buf[1024];
   gint chars_read;
   GtkTextIter iter;
   chars_read = 1024;
   


GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
GtkWidget *scrollbar;
int id ;

       // GtkWidget *button = gtk_button_new_with_label("Lancer l'enchére");
    //    GtkWidget *button1 = gtk_button_new_with_label("Afficher pdt");
        gchar *title;

GtkWidget *hbox10,*image,*hbox11,*hbox12,*hbox13,*vbox11,*vbox0,*vbox,*vbox1,*vbox2,*vbox3,*vbox4,*hbox2,*hbox4,*hbox3,*hbox,*hbox1,*label,*label1,*label1r,*label2,*label2r,*label3,*label3r,*entry;
   

/*********************buffer************************************/

// Create a pipe. File descriptors for the two ends of the pipe are placed in fds.
   pipe (fds);
   // Redirect fds[1] to be writed with the standard output.
   dup2 (fds[1], STDOUT_FILENO);

/***********************************************************/

 g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);


/*id=atof(gtk_entry_get_text(GTK_ENTRY(data)));**/

f=fopen("fichier.txt","r+");

while(feof(f)){
fscanf(f," %d %s %s %d %d \n",&(e.id),e.nature,e.model,&(e.quantite),&(e.prix)); 
if(e.id == id)
prie=e.prix;
 
}
fclose(f);
//************************buffer*********************************************//

/*GtkTextIter start;
GtkTextIter end;*/
//GtkTextBuffer *buffer;
//gchar lecture[1024];

    

     text_view=gtk_text_view_new();



//saisie_buffer("bonjour karim\n");




//declare thread

memset(&hints, 0, sizeof hints);//Zero the whole structure before use with memset()

hints.ai_family = AF_UNSPEC;  // AF_INET designe IPV4 &&AF_UNSPEC for both "IPV4 ,IPV6"
hints.ai_socktype = SOCK_STREAM;
hints.ai_flags = AI_PASSIVE; // use my IP-> if i use AI_PASSIVE the node name wil be "NULL" && INADDR_ANY=IPV4


if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {// NULL -> is the node name && return information on a particular host name

fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));// gestion des erreurs
//return 1;
}




// loop through all the results and bind to the first we can
for(p = servinfo; p != NULL; p = p->ai_next) {

if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
perror("server: socket");
continue;
}


if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
close(sockfd);
perror("server: bind");
continue;
}


break;
}

freeaddrinfo(servinfo); // all done with this structure

if (p == NULL) {
fprintf(stderr, "server: failed to bind\n");
exit(1);
}



//printf("server: waiting for connections...\n");
saisie_buffer(0, 0,0);


if (listen(sockfd, BACKLOG) == -1) {  // listen
perror("listen");
//exit(1);
}


if (pthread_mutex_init(&mutex, NULL) != 0) 
    { 
        printf("\n mutex init has failed\n"); 
       // return 1; 
    } 

int tab[255];
int resultat;
int j=0;



// GtkWidget *label0 = gtk_label_new ("not updated yet...");
 // g_timeout_add (1000 /* milliseconds */, on_timeout, label0);


/*****code problem*****************/


if(pthread_create(&systems,NULL,(void*)auction,NULL) != 0)
close(sockfd);

/*
if( fork() == 0)
{
while(1)
    {
        sin_size = sizeof their_addr;
     new_socket = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);

if(new_socket<0)
 printf("erreur de creation du socket\n");



if(pthread_create(&client[i],NULL,(void*)client_connect_to_server,&new_socket) != 0)
close(sockfd);


 
i++;


}
*/

wait(NULL);
// close(new_socket);







/*****code problem*****************/




  
  /*  gtk_text_buffer_get_start_iter(buffer,&start);
    gtk_text_buffer_get_end_iter(buffer,&end);
    gtk_text_buffer_delete(buffer, &start, &end);*/
  /*   
    while(fgets(lecture, 1024, fichier))
    {
        gtk_text_buffer_get_end_iter(buffer,&end);
        gtk_text_buffer_insert(buffer, &end, g_locale_to_utf8(lecture, -1, NULL, NULL, NULL), -1);*/
    //}

//************************buffer*********************************************//






 scrollbar = gtk_scrolled_window_new(NULL, NULL);
   // gtk_box_pack_start(GTK_BOX(box), scrollbar, TRUE, TRUE, 5);
     

    gtk_container_add(GTK_CONTAINER(scrollbar),text_view);


    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrollbar), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);


       //   entry=gtk_entry_new();







label=gtk_label_new("Interface D'enchére");
  label1=gtk_label_new("NB Participants");
   label1r=gtk_label_new("0");    
//pthread_create(&nb_participant,NULL,(void*)set_nb_participant,label1r) ;
   label2=gtk_label_new("PRIX DU DEBUT");
  label2r=gtk_label_new("100");  
  
  label3=gtk_label_new("PRIX FINAL");
  label3r=gtk_label_new("100");  
 //pthread_create(&nb_participant,NULL,(void*)set_prix_finale,label3r) ;

image=gtk_image_new_from_file("/home/karim/Desktop/img.jpeg");

  hbox=gtk_hbox_new(0,0);
  hbox1=gtk_hbox_new(10,10);
  hbox2=gtk_hbox_new(10,10);
  hbox3=gtk_hbox_new(10,10);
  hbox4=gtk_hbox_new(10,10);
 hbox11=gtk_hbox_new(10,10);
 hbox12=gtk_hbox_new(10,10);
 hbox13=gtk_hbox_new(10,10);
hbox10=gtk_hbox_new(10,10);

vbox0=gtk_vbox_new(0,10);
vbox=gtk_vbox_new(0,10);
vbox1=gtk_vbox_new(0,10);
vbox2=gtk_vbox_new(0,10);
vbox3=gtk_vbox_new(0,10);
vbox4=gtk_vbox_new(0,10);
vbox11=gtk_vbox_new(0,10);



gtk_box_pack_start(GTK_BOX(vbox),(label),1,1,20);
//gtk_box_pack_start(GTK_BOX(hbox10),(hbox11),1,1,20);
//gtk_box_pack_start(GTK_BOX(hbox10),(image),1,1,20);
//gtk_box_pack_start(GTK_BOX(hbox10),(hbox12),1,1,20);
//gtk_box_pack_start(GTK_BOX(hbox10),(label),1,1,20);
//tk_box_pack_start(GTK_BOX(hbox10),(hbox13),1,1,20);
//gtk_box_pack_start(GTK_BOX(hbox10),(image),1,1,20);


gtk_box_pack_start(GTK_BOX(vbox),hbox,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox),hbox1,1,1,20);



gtk_box_pack_start(GTK_BOX(hbox1),hbox1,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox1),scrollbar,1,20,20);

gtk_box_pack_start(GTK_BOX(hbox1),vbox0,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox0),vbox1,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox1),label1,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox1),label1r,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox0),vbox3,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox3),label2,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox3),label2r,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox0),vbox4,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox4),label3,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox4),label3r,1,1,20);
//gtk_box_pack_start(GTK_BOX(vbox3),label3,1,1,20);
//gtk_box_pack_start(GTK_BOX(vbox3),label3r,1,1,20);





        
        /* add window to list */
        
        app->windows = g_slist_prepend (app->windows, window);
        
        /* setup window and pack a button into it */
        
       // gtk_container_set_border_width (GTK_CONTAINER (window), 25);
       //


      gtk_container_add (GTK_CONTAINER (window), vbox);



        title = g_strdup_printf ("Window %d", g_slist_length (app->windows));
        gtk_window_set_title (GTK_WINDOW (window), title);
        g_free (title);
        
      
      gtk_widget_set_size_request(window,550,630);


        /* connect callbacks to signals */
        
        g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);



   //gdk_input_add(fds[0], GDK_INPUT_READ, server, NULL);

     // g_signal_connect (G_OBJECT (text_view), NULL, 
                     //    G_CALLBACK(server), NULL);
        
      //gdk_input_add(text_view, GDK_INPUT_READ, server, NULL);
                                   
      /*  g_signal_connect (G_OBJECT (button1), "clicked", 
                          G_CALLBACK (afficher_pdt), app);

                 g_signal_connect(entry, "activate", G_CALLBACK(NULL), entry);*/






        gtk_widget_show_all (window); 



}




void pdt_encherire(GtkWidget *widget, MyApp *app)
{
       GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL),*image;
        GtkWidget *button = gtk_button_new_with_label("Lancer l'enchére");
         GtkWidget *button1 = gtk_button_new_with_label("verifier : ");
        gchar *title;
        image=gtk_image_new_from_file("/home/karim/Desktop/12.jpeg");
GtkWidget *vbox,*vbox1,*vbox2,*hbox2,*hbox,*hbox1,*label,*entry,*label2;
   
  label=gtk_label_new("Entrer ID de PDT a'enchérire");
     label2=gtk_label_new("");
        entry=gtk_entry_new();

  hbox=gtk_hbox_new(0,0);
  hbox1=gtk_hbox_new(0,0);
vbox=gtk_vbox_new(0,10);
vbox1=gtk_vbox_new(0,10);


gtk_box_pack_start(GTK_BOX(vbox),image,1,1,0);

gtk_box_pack_start(GTK_BOX(vbox),hbox,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox),label,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox),entry,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox1),button1,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox1),label2,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox),button,1,1,20);

/*gtk_box_pack_start(GTK_BOX(vbox1),button,1,1,0);
gtk_box_pack_start(GTK_BOX(vbox1),hbox,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),label2,1,1,0);
     
gtk_box_pack_start(GTK_BOX(hbox),entry,1,1,0);

gtk_box_pack_start(GTK_BOX(vbox1),button1,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox1),image,1,1,0);*/


/*

gtk_box_pack_start(GTK_BOX(hbox),vbox1,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),vbox1,1,1,0);
gtk_box_pack_start(GTK_BOX(vbox1),label,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),vbox1,1,1,0);*/






        
        /* add window to list */
        
        app->windows = g_slist_prepend (app->windows, window);
        
        /* setup window and pack a button into it */
        
       // gtk_container_set_border_width (GTK_CONTAINER (window), 25);
       //


      gtk_container_add (GTK_CONTAINER (window), vbox);



        title = g_strdup_printf ("Window %d", g_slist_length (app->windows));
        gtk_window_set_title (GTK_WINDOW (window), title);
        g_free (title);
        
      
      gtk_widget_set_size_request(window,600,450);


        /* connect callbacks to signals */
        
        g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);
       

          /*  g_signal_connect (G_OBJECT (button), "clicked", 
                          G_CALLBACK (interface_enchere), entry);*/
        
       g_signal_connect (G_OBJECT (button), "clicked", 
                          G_CALLBACK (interface_enchere), app);
                                       


      /*  g_signal_connect (G_OBJECT (button1), "clicked", 
                          G_CALLBACK (afficher_pdt), app);

                 g_signal_connect(entry, "activate", G_CALLBACK(NULL), entry);*/

        gtk_widget_show_all (window); 
}


//part 2

void afficher_pdt(GtkWidget *widget, MyApp *app)
{
        GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        GtkWidget *button = gtk_button_new_from_stock (GTK_STOCK_ADD);
        gchar *title;
        
        /* add window to list */
        
    /*    app->windows = g_slist_prepend (app->windows, window);
        
        /* setup window and pack a button into it */
        
       // gtk_container_set_border_width (GTK_CONTAINER (window), 25);
       //

/*
      gtk_container_add (GTK_CONTAINER (window), button);
        title = g_strdup_printf ("Window %d", g_slist_length (app->windows));
        gtk_window_set_title (GTK_WINDOW (window), title);
        g_free (title);
        
        /* connect callbacks to signals */
    /*    
        g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);
        
        g_signal_connect (G_OBJECT (button), "clicked", 
                          G_CALLBACK (on_add_button_clicked), app);
                                       
        
        gtk_widget_show_all (window);   */  
}




void on_activate_entry_nature(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;



f=fopen("fichier.txt","r+");

fseek(f,0,2);





    /* Recuperation du texte contenu dans le GtkEntry */
    sText = gtk_entry_get_text(GTK_ENTRY(data));
     sprintf(e.nature, "%s",sText);
fprintf(f,"%s  ",e.nature);
        fclose(f);
  printf(" le nature est %s \n",e.nature);

}



void on_activate_entry_model(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;
   


f=fopen("fichier.txt","r+");

fseek(f,0,2);




    
    /* Recuperation du texte contenu dans le GtkEntry */
    sText = gtk_entry_get_text(GTK_ENTRY(data));
    sprintf(e.model, "%s",sText);
   fprintf(f,"%s  ",e.model);
        
        fclose(f);

 printf(" le model est %s",e.model);

}


void on_activate_entry_id(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;



f=fopen("fichier.txt","r+");

fseek(f,0,2);




    /* Recuperation du texte contenu dans le GtkEntry */


    
e.id=atoi(gtk_entry_get_text(GTK_ENTRY(data)));

fprintf(f," %d  ",e.id);

        fclose(f);
// e.id = strtoul(sText, &ptr, 10);
printf(" le id  est %d \n",e.id);


  
}
 

void on_activate_entry_prix(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;



f=fopen("fichier.txt","r+");

fseek(f,0,2);




    /* Recuperation du texte contenu dans le GtkEntry */
e.prix=atoi(gtk_entry_get_text(GTK_ENTRY(data)));
 
  //e.prix=atof

fprintf(f,"%d \n",e.prix);

        fclose(f);
printf(" le prix est %d \n",e.prix);

}


void on_activate_entry_quantite(GtkWidget *pEntry, gpointer data)
{
    const gchar *sText;




f=fopen("fichier.txt","r+");

fseek(f,0,2);





    /* Recuperation du texte contenu dans le GtkEntry */
e.quantite=atoi(gtk_entry_get_text(GTK_ENTRY(data)));
 fprintf(f,"%d ",e.quantite);
        fclose(f);
  //e.quantite=atoi(sText);
printf(" le quantite est %d \n",e.quantite);



}

/*void enregistrer_file(GtkWidget *pEntry, gpointer data)
{




}*/
 
 




void ajout_pdt(GtkWidget *widget, MyApp *app)
{
       GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL),*image,*Entrer;
        GtkWidget *button = gtk_button_new_with_label("Ajouter");
        GtkWidget *button1 = gtk_button_new_with_label("Afficher pdt");
        gchar *title;
        image=gtk_image_new_from_file("/home/karim/Desktop/12.jpeg");
GtkWidget *vbox,*hbox2,*hbox3,*hbox4,*hbox5,*hbox,*hbox6,*hbox1,*label,*label6,*label1,*label3,*label5,*label4,*entry,*entry1,*entry2,*entry3,*entry4,*entry5,*label2;
   
//fichier
FILE *f;
produit e;




  label=gtk_label_new("Ajout Produit");
label1=gtk_label_new("entrer ID : ");
  label2=gtk_label_new("NATURE pdt : ");
  label3=gtk_label_new("MODEL pdt : ");
  label4=gtk_label_new("Quantite pdt : ");
  label5=gtk_label_new("prix Pdt : ");
  label6 = gtk_label_new(NULL);
        entry=gtk_entry_new();
        entry1=gtk_entry_new();
        entry2=gtk_entry_new();
        entry3=gtk_entry_new();
        entry4=gtk_entry_new();

 hbox=gtk_hbox_new(0,0);
vbox=gtk_vbox_new(0,10);
hbox1=gtk_hbox_new(0,10);
hbox2=gtk_hbox_new(0,10);
hbox3=gtk_hbox_new(0,10);
hbox4=gtk_hbox_new(0,10);
hbox5=gtk_hbox_new(0,10);


/*Entrer = gtk_entry_new_with_max_length(100);
gtk_entry_set_editable(GTK_ENTRY(Entrer), NULL);
    gtk_entry_set_alignment(GTK_ENTRY(Entrer), TRUE);
    gtk_entry_set_has_frame(GTK_ENTRY(Entrer),NULL);*/


gtk_box_pack_start(GTK_BOX(vbox),label,1,1,0);

gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox1),label1,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox1),entry,1,1,20);
/*const gchar *ids;
ids=gtk_entry_get_text (GTK_ENTRY(entry));
e.id=atoi(ids);*/

gtk_box_pack_start(GTK_BOX(vbox),hbox2,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox2),label2,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox2),entry1,1,1,20);
/*const gchar *natures;
natures=gtk_entry_get_text (GTK_ENTRY(entry1));
sprintf(e.nature, "%s",natures);
//e.nature=((char*)gtk_label_get_text (entry1));*/

gtk_box_pack_start(GTK_BOX(vbox),hbox3,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox3),label3,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox3),entry2,1,1,20);
/*sprintf(e.model, "%s", gtk_entry_get_text (GTK_ENTRY(entry2)));
//e.model=((char*)gtk_label_get_text (entry2));*/

gtk_box_pack_start(GTK_BOX(vbox),hbox4,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox4),label4,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox4),entry3,1,1,20);
/*e.quantite= atoi(gtk_entry_get_text (GTK_ENTRY(entry3)));*/

gtk_box_pack_start(GTK_BOX(vbox),hbox5,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox5),label5,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox5),entry4,1,1,20);
/*sprintf(e.prix, "%f", gtk_label_get_text (entry4));
e.prix=atof(gtk_entry_get_text (GTK_ENTRY(entry4)));*/

gtk_box_pack_start(GTK_BOX(vbox),button,1,1,20);


	



        
        /* add window to list */
        
        app->windows = g_slist_prepend (app->windows, window);
        
        /* setup window and pack a button into it */
        
       // gtk_container_set_border_width (GTK_CONTAINER (window), 25);
       //


      gtk_container_add (GTK_CONTAINER (window), vbox);



        title = g_strdup_printf ("Window %d", g_slist_length (app->windows));
        gtk_window_set_title (GTK_WINDOW (window), title);
        g_free (title);
        
      
      gtk_widget_set_size_request(window,600,450);


        /* connect callbacks to signals */
        
        g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);
        
     /* g_signal_connect (G_OBJECT (button), "clicked", 
                          G_CALLBACK (take_value_input), app);
                                       


      /*  g_signal_connect (G_OBJECT (button1), "clicked", 
                          G_CALLBACK (afficher_pdt), app);*/

g_signal_connect(button, "clicked", G_CALLBACK(on_activate_entry_id), entry);

g_signal_connect(button, "clicked", G_CALLBACK(on_activate_entry_nature), entry1);
g_signal_connect(button, "clicked", G_CALLBACK(on_activate_entry_model), entry2);
g_signal_connect(button, "clicked", G_CALLBACK(on_activate_entry_quantite), entry3);
g_signal_connect(button, "clicked", G_CALLBACK(on_activate_entry_prix), entry4);

//printf(" tesssssttt %d  %s  %s %d %f \n",e.id,e.nature ,e.model,e.quantite,e.prix);






//printf(" tesssssttt %d  %s  %s %d %f \n",e.id,e.nature ,e.model,e.quantite,e.prix);





        gtk_widget_show_all (window); 
}







//part 1*/

void gestion_stock(GtkWidget *widget, MyApp *app)
{
      GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL),*image;
        GtkWidget *button = gtk_button_new_with_label("ajout pdt");
        GtkWidget *button1 = gtk_button_new_with_label("Afficher pdt");
        gchar *title;
        image=gtk_image_new_from_file("/home/karim/Desktop/download.jpeg");
GtkWidget *vbox,*vbox1,*vbox2,*hbox2,*hbox,*hbox1,*label,*entry,*label2;
   
  label=gtk_label_new("Gerer mon stock");
label2=gtk_label_new("supprimer pdt\n(entrer ID)");
        entry=gtk_entry_new();

  hbox=gtk_hbox_new(0,0);
  hbox1=gtk_hbox_new(0,0);
vbox=gtk_vbox_new(0,10);
vbox1=gtk_vbox_new(0,10);


gtk_box_pack_start(GTK_BOX(vbox),label,1,1,0);

gtk_box_pack_start(GTK_BOX(vbox),hbox1,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox1),vbox1,1,1,20);
gtk_box_pack_start(GTK_BOX(vbox1),button,1,1,0);
gtk_box_pack_start(GTK_BOX(vbox1),hbox,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),label2,1,1,0);
     
gtk_box_pack_start(GTK_BOX(hbox),entry,1,1,0);

gtk_box_pack_start(GTK_BOX(vbox1),button1,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox1),image,1,1,0);


/*

gtk_box_pack_start(GTK_BOX(hbox),vbox1,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),vbox1,1,1,0);
gtk_box_pack_start(GTK_BOX(vbox1),label,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),vbox1,1,1,0);*/






        
        /* add window to list */
        
        app->windows = g_slist_prepend (app->windows, window);
        
        /* setup window and pack a button into it */
        
       // gtk_container_set_border_width (GTK_CONTAINER (window), 25);
       //


      gtk_container_add (GTK_CONTAINER (window), vbox);



        title = g_strdup_printf ("Window %d", g_slist_length (app->windows));
        gtk_window_set_title (GTK_WINDOW (window), title);
        g_free (title);
        
      
      gtk_widget_set_size_request(window,600,450);


        /* connect callbacks to signals */
        
        g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);
        
        g_signal_connect (G_OBJECT (button), "clicked", 
                          G_CALLBACK (ajout_pdt), app);
                                       
        g_signal_connect (G_OBJECT (button1), "clicked", 
                          G_CALLBACK (afficher_pdt), app);

                 g_signal_connect(entry, "activate", G_CALLBACK(NULL), entry);

        gtk_widget_show_all (window);    
}




//menu principale

void menu_principale(GtkWidget *widget, MyApp *app)
{
        GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL),*image;
        GtkWidget *button = gtk_button_new_with_label("PDT a'enchérire");
        GtkWidget *button1 = gtk_button_new_with_label("Gestion De Stock");
        gchar *title;
        image=gtk_image_new_from_file("/home/karim/Desktop/enchere.jpeg");
GtkWidget *vbox,*vbox1,*hbox,*label;
 
     label=gtk_label_new("hello world");




  hbox=gtk_hbox_new(0,0);
vbox=gtk_vbox_new(0,10);
vbox1=gtk_vbox_new(0,10);
gtk_box_pack_start(GTK_BOX(vbox),image,1,1,0);
gtk_box_pack_start(GTK_BOX(vbox),hbox,1,1,0);

gtk_box_pack_start(GTK_BOX(hbox),button,1,1,20);
gtk_box_pack_start(GTK_BOX(hbox),button1,1,1,20);


gtk_box_pack_start(GTK_BOX(vbox),label,1,1,0);

        
        /* add window to list */
        
        app->windows = g_slist_prepend (app->windows, window);
        
        /* setup window and pack a button into it */
        
       // gtk_container_set_border_width (GTK_CONTAINER (window), 25);
       //


      gtk_container_add (GTK_CONTAINER (window), vbox);




        title = g_strdup_printf ("Window %d", g_slist_length (app->windows));
        gtk_window_set_title (GTK_WINDOW (window), title);
        g_free (title);
        
       gtk_widget_set_size_request(window,600,450);
gtk_widget_set_size_request(button,30,35);
gtk_widget_set_size_request(button1,30,35);

        /* connect callbacks to signals */
        
        g_signal_connect (G_OBJECT (window), "destroy", 
                          G_CALLBACK (on_window_destroy), app);
        
        g_signal_connect (G_OBJECT (button), "clicked", 
                          G_CALLBACK (pdt_encherire), app);
                                       
        g_signal_connect (G_OBJECT (button1), "clicked", 
                          G_CALLBACK (gestion_stock), app);



        gtk_widget_show_all (window);   

}



int main (int argc, char *argv[])
{
        MyApp *app;
        
        gtk_init (&argc, &argv);


        app = g_slice_new (MyApp);

        app->windows = NULL;
        
        /* create first window */
       menu_principale(NULL, app);
        
        gtk_main ();
        g_slice_free (MyApp, app);
        
        return 0;               

 //  gtk_text_buffer_set_text (p_buf,donner, -1);
}
