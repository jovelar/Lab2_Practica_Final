#include <stdio.h>
#include <stdlib.h>


typedef struct
{
    int id;
    char nombreProducto[80];
    char marca[50];
    float precio;
    char tipo[50];
}Producto;

int main()
{
    crearRegistros("RegistroAlimentos.bin");	
}

void crearRegistros(char nombreArchivo[40])
{
    FILE *archivo=fopen(nombreArchivo,"wb");

    Producto productos[]={
        {1,"Yogur Entero 1L","Coto",1199.25,"Lacteo"},
        {2,"Yogur Entero 160gr","Tregar",1150.00,"Lacteo"},
        {3,"Yogur Entero con Frutas","Milkaut",1149.00,"Lacteo"},
        {4,"Yogur Entero con Cereales","Tregar",1100.00,"Lacteo"},
        {5,"Leche Larga Vida Entera 1L","Coto",949.00,"Lacteo"},
        {6,"Leche Parc. Descremada 1L","Coto",949.00,"Lacteo"},
        {7,"Leche entera sachet 1L","Coto",929.00,"Lacteo"},
        {8,"Leche entera clasica 1L","La Serenisima",1801.90,"Lacteo"},
        {9,"Leche parcialmente descremada 1L","La Serenisima",1801.90,"Lacteo"},
        {10,"Queso Untable Mascarpone","Tregar",2300.00,"Lacteo"},
        {11,"Queso Crema","La Paulina",1125.25,"Lacteo"},
        {12,"Queso Doble Crema","La Paulina",1287.65,"Lacteo"},
        {13,"Queso Untable Clasico","Milkaut",1749.00,"Lacteo"},
        {14,"Queso Gruyere x KG","Veronica",18159.00,"Lacteo"},
        {15,"Queso Pategras x KG","Veronica",16259.00,"Lacteo"},
        {16,"Queso Azul x KG","Veronica",18359.00,"Lacteo"},
        {17,"Queso Port Salud","Veronica",10579.00,"Lacteo"},
        {18,"Mermelada Ciruela","El Brocal",2304.25,"Conserva"},
        {19,"Mermelada Durazno","El Brocal",2187.25,"Conserva"},
        {20,"Dulce de leche","Coto",2308.97,"Conserva"},
        {21,"Dulce de leche repostero","Coto",1789.00,"Conserva"},
        {22,"Dulce de leche","Poncho Negro",3587.00,"Conserva"},
        {23,"Dulce de leche clasico","Milkaut",2540.00,"Conserva"},
        {24,"Dulce de leche","Ilolay",2380.50,"Conserva"},
        {25,"Postre vainilla","Exquisita",990.00,"Postre"},
        {26,"Postre royal","Royal",805.00,"Postre"},
        {27,"Flan sabor vainilla","Godet",427.00,"Postre"},
        {28,"Postre dulce de leche","Shimy",1579.50,"Postre"},
        {29,"Frambuesas con doble chocolate","Gio",4669.00,"Postre"},
        {30,"Postre helado block","Cofler",4679.35,"Postre"},
        {31,"Paleta cocida x kg","Paladini",10295.00,"Fiambre"},
        {32,"Salchicha paladini","Paladini",1515.00,"Fiambre"},
        {33,"Mortadela mini","Campo Austral",1918.95,"Fiambre"},
        {34,"Mini salchichon triple","Paladini",2630.00,"Fiambre"},
        {35,"Bondiola feteada x kg","Lario",3415.00,"Fiambre"},
        {36,"Fiambre de cerdo feteado x kg","Campo Austral",8449.00,"Fiambre"},
        {37,"Salame milan","Paladini",3499.00,"Fiambre"},
        {38,"Salamin tandilero","Cagnoli",15900.00,"Fiambre"},
        {39,"Coca cola zero 350ml","Coca Cola",1150.00,"Gaseosa"},
        {40,"Coca cola ligth 2.5L","Coca Cola",2030.00,"Gaseosa"},
        {41,"Coca cola 500ml","Coca Cola",1150.00,"Gaseosa"},
        {42,"Coca cola original 2.5L","Coca cola",1809.00,"Gaseosa"},
        {43,"7 Up 500ml","PepsiCo",893.00,"Gaseosa"},
        {44,"7 Up 250ml","PepsiCo",496,"Gaesosa"},
        {45,"Cunnington Cola","Cunnington",1510.00,"Gaseosa"},
        {46,"Cunnington Pomelo","Cunnington",1510.00,"Gaseosa"},
        {47,"Schweppers Tonica","Schweppers",2300.00,"Gaseosa"},
        {48,"Schweppers Zero Pomelo","Schweppers",2300,"Gaseosa"},
        {49,"Fanta Naranja 2.5L","Coca cola",2750.00,"Gaseosa"},
        {50,"Jugo Citric Naranja 500ML","Citric",1114.75,"Jugo"},
        {51,"Jugo Naranja 1L","Puro Sol",1898.90,"Jugo"},
        {52,"Jugo Manzana 1L","Pura Frutta",2134.11,"Jugo"},
        {53,"Jugo Pomelo 1L","Puro Sol",1898.90,"Jugo"},
        {54,"Jugo naranja y durazno 1L","Puro Sol",1898.90,"Jugo"},
        {55,"Jugo naranja 500ml","Smudis",2095.50,"Jugo"},
        {56,"Vino Alfredo Coto Cabernet Sauvignon 750ML","Coto",2855.00,"Vino"},
        {57,"Vino Alfredo Coto Malbec","Coto",2855.00,"Vino"},
        {58,"Vino Cosecha Tardia 750ML","Benjamin Blanco",2160.00,"Vino"},
        {59,"Vino Cabernet Savignon 750ML","Fran",2520.00,"Vino"},
        {60,"Vino Blend Tinto 750ML","Don Nicanor",6420.00,"Vino"},
        {61,"Vino Chardonnay 750ML","Nieto Senetiner",4080.00,"Vino"},
        {62,"Vino Malbec 750ML","Trumpeter",16100.00,"Vino"},
        {63,"Vino Merlot 750ML","Reserva Sophenia",7020.00,"Vino"},
        {64,"Vino Chardonnay 750ML","Maria Carmen",65300.00,"Vino"}};


        fwrite(productos,sizeof(Producto),63,archivo);
        pasarACSV(productos,63,"Registros.csv");


    fclose(archivo);
}