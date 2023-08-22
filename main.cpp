
#include <iostream>
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <gtk/gtk.h>
#include "JsonBox.h"

#include "include/diag.hpp"

#if defined(_WIN32) || defined(WIN32)
    #include <gdk/gdkwin32.h>
#elif defined(__unix__) || defined(__unix) || defined(unix) || defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__)
#else
#endif

#define MAX_LABEL_LENGTH 20
// ========================================================================================================================

    GtkBuilder  *gbuilder;
    GError      *gerror = NULL;

    GtkWidget   *gtk_window;
    GtkWidget   *button_1;
    GtkWidget   *button_2;
    GtkWidget   *button_3;
    GtkWidget   *button_4;
    GtkWidget   *button_5;
    GtkWidget   *button_6;
    GtkWidget   *button_7;
    GtkWidget   *button_8;
    GtkWidget   *button_9;
    GtkWidget   *button_0;
    GtkWidget   *button_plus;
    GtkWidget   *button_minus;
    GtkWidget   *button_dot;
    GtkWidget   *button_equal;
    GtkWidget   *button_divide;
    GtkWidget   *button_plusminus;
    GtkWidget   *button_percent;
    GtkWidget   *button_C;
    GtkWidget   *button_multiply;
    GtkWidget   *label;
    GtkWidget   *txt1;
    GtkWidget   *txt2;
    std::string check;
    double firstNum;
    bool eq;
    std::string his;


    void on_gtk_digit__clicked(GtkButton *button, gpointer user_data)
    {
        const char *button_label = gtk_button_get_label(button);
        const char *current_label = gtk_label_get_text(GTK_LABEL(label));

        if (strlen(current_label) < MAX_LABEL_LENGTH) {

            char new_label[MAX_LABEL_LENGTH + 1];
            if(eq || strcmp(current_label, "0") == 0)
            {
                snprintf(new_label, sizeof(new_label), "%s", button_label);
                eq = false;
                gtk_label_set_text(GTK_LABEL(label), new_label);
            }
            else
            {
                snprintf(new_label, sizeof(new_label), "%s%s", current_label, button_label);
                eq = false;
                gtk_label_set_text(GTK_LABEL(label), new_label);
            }
        }

    }

    void operation_clicked(GtkButton *button, gpointer user_data)
    {
        const char *button_label = gtk_button_get_label(button);
        const char *current_label = gtk_label_get_text(GTK_LABEL(label));
        std::string str(current_label);
        if(strcmp(button_label, "+\\-") == 0)
        {
            if(str != "0")
            {

                double number = std::stod(str);
                number *= -1;
                char buffer[100];
                sprintf(buffer, "%.15g", number);
                gtk_label_set_text(GTK_LABEL(label), buffer);
            }
            DIAG_BUFF("+\\- clicked", 4);
        }
        else if(strcmp(button_label, "C") == 0)
        {
            if(str.size() > 0) {
                str.erase(str.size()-1, 1); // Usuniêcie ostatniego znaku
                if(str != "")
                    gtk_label_set_text(GTK_LABEL(label), str.c_str()); // Konwersja std::string na const char*
                else
                    gtk_label_set_text(GTK_LABEL(label), "0");
            }
            DIAG_BUFF("C clicked", 4);
        }
        else if(strcmp(button_label, ".") == 0)
        {
            if(str.find(",") == std::string::npos)
            {
                str += ",";
                gtk_label_set_text(GTK_LABEL(label), str.c_str());
            }
            DIAG_BUFF("dot clicked", 4);
        }
        else if(strcmp(button_label, "CE") == 0)
        {
            gtk_label_set_text(GTK_LABEL(label), "0");
            eq = false;
            check = "";
            GtkTextBuffer *buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt2));
            gtk_text_buffer_set_text(buffer1, "", -1);
            DIAG_BUFF("CE clicked", 4);
        }
        DIAG_OUT;
    }


    void math_clicked(GtkButton *button, gpointer user_data)
    {
        const char *button_label = gtk_button_get_label(button);
        const char *current_label = gtk_label_get_text(GTK_LABEL(label));
        std::string str(current_label);
        double num1 = std::stod(str);
        GtkTextBuffer *buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt2));
        char txt[100];

        if(strcmp(button_label, "+") == 0)
        {
            check = "plus";
            firstNum = num1;
            eq = true;
            sprintf(txt, "%.15g +", firstNum);
            //gtk_label_set_text(GTK_LABEL(label), "0");
        }
        if(strcmp(button_label, "-") == 0)
        {
            check = "minus";
            firstNum = num1;
            eq = true;
            sprintf(txt, "%.15g -", firstNum);
            //gtk_label_set_text(GTK_LABEL(label), "0");
        }
        if(strcmp(button_label, "*") == 0)
        {
            check = "multiply";
            firstNum = num1;
            eq = true;
            sprintf(txt, "%.15g *", firstNum);
            //gtk_label_set_text(GTK_LABEL(label), "0");
        }
        if(strcmp(button_label, "/") == 0)
        {
            check = "divide";
            firstNum = num1;
            eq = true;
            sprintf(txt, "%.15g /", firstNum);
            //gtk_label_set_text(GTK_LABEL(label), "0");
        }
        gtk_text_buffer_set_text(buffer1, txt, -1);
    }

    void equal_clicked(GtkButton *button, gpointer user_data)
    {
        const char *button_label = gtk_button_get_label(button);
        const char *current_label = gtk_label_get_text(GTK_LABEL(label));
        std::string str(current_label);
        double secondNum = std::stod(str);
        double result;
        char txt[1000];
        GtkTextBuffer *buffer1 = gtk_text_view_get_buffer(GTK_TEXT_VIEW(txt1));
        if(check != "")
            eq = true;

        if(check == "plus")
        {
            result = firstNum + secondNum;
            char buffer[100];
            sprintf(buffer, "%.15g", result);
            gtk_label_set_text(GTK_LABEL(label), buffer);
            sprintf(txt, "%.15g + %.15g = %.15g\n", firstNum, secondNum, result);
            his += txt;
            DIAG_BUFF(txt,3);
            DIAG_OUT;
        }
        if(check == "minus")
        {
            result = firstNum - secondNum;
            char buffer[100];
            sprintf(buffer, "%.15g", result);
            gtk_label_set_text(GTK_LABEL(label), buffer);
            sprintf(txt, "%.15g - %.15g = %.15g\n", firstNum, secondNum, result);
            his += txt;
            DIAG_BUFF(txt,3);
            DIAG_OUT;
        }
        if(check == "divide")
        {
            result = firstNum / secondNum;
            char buffer[100];
            sprintf(buffer, "%.15g", result);
            gtk_label_set_text(GTK_LABEL(label), buffer);
            sprintf(txt, "%.15g / %.15g = %.15g\n", firstNum, secondNum, result);
            his += txt;
            DIAG_BUFF(txt,3);
            DIAG_OUT;
        }
        if(check == "multiply")
        {
            result = firstNum + secondNum;
            char buffer[100];
            sprintf(buffer, "%.15g", result);
            gtk_label_set_text(GTK_LABEL(label), buffer);
            sprintf(txt, "%.15g * %.15g = %.15g\n", firstNum, secondNum, result);
            his += txt;
            DIAG_BUFF(txt,3);
            DIAG_OUT;
        }
        gtk_text_buffer_set_text(buffer1, his.c_str(), -1);
    }


    static gboolean on_window_closed(GtkWidget* widget, GdkEvent* event, gpointer user_data)
    {
        DIAG_BUFF("Program zamknieto",1);
        DIAG_OUT;

        return FALSE;
    }
// ========================================================================================================================

std::string windowTitle()
{
    JsonBox::Value json;
    json.loadFromFile("params.json");
    std::string title;

    // Sprawdzenie, czy obiekt "window" istnieje
    if (json["window"].isObject()) {
        JsonBox::Object window = json["window"].getObject();

        // Sprawdzenie, czy obiekt "parameters" istnieje
        if (window["parameters"].isObject()) {
            JsonBox::Object parameters = window["parameters"].getObject();

            // Sprawdzenie, czy pole "title" istnieje
            if (parameters["title"].isString()) {
                title = parameters["title"].getString();
                std::cout << "Wartość pola 'title': " << title << std::endl;
            }
        }
    }
    return title;
}

int main( int argc, char *argv[]) {


    std::string text = "ALA MA KOTA";
    std::string text2 = "JEST SUPER123";

    regist::init();

    //gtk_init(&argc, &argv);
    if(!gtk_init_check(&argc, &argv))
    {
        DIAG_BUFF("Inicjalizacja gtk nie powiodla sie", 1);
        DIAG_OUT;
    }
    else
    {
        DIAG_BUFF("Inicjalizacja gtk powiodla sie", 1);
        DIAG_OUT;
    }

    // wczytamy widgety z pliku *.glade za pomoca GtkBuilder
    gbuilder = gtk_builder_new();

    if (!gtk_builder_add_from_file(gbuilder, "Calculator.glade", &gerror)) {
        auto errMsg = "GBuilder error: " + std::string(gerror->message);
        DIAG_BUFF(errMsg, 1);
        DIAG_OUT;
        g_free(gerror);
        return 1; // wyjście z programu z kodem informacji o błędzie
    }
    else
    {
        DIAG_BUFF("Dodano builder z pliku", 2);
        DIAG_OUT;

    }


    // gbuilder ma informacje o wszystkich widgetach zdefiniowanych w pliku glade
    // ponizej podpinamy recznie po kolei widgety o zadanych identyfikatorach do zmiennych GtkWidget* zdefiniowanych w naszym programie
    // podpinamy tylko te widgety, z ktorych zamierzamy korzystac

    gtk_window = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "gtk_window" ) );
    button_1 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_1" ) );
    button_2 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_2" ) );
    button_3 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_3" ) );
    button_4 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_4" ) );
    button_5 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_5" ) );
    button_6 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_6" ) );
    button_7 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_7" ) );
    button_8 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_8" ) );
    button_9 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_9" ) );
    button_0 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_0" ) );

    button_plus = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_plus" ) );
    button_minus = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_minus" ) );
    button_divide = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_divide" ) );
    button_C = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_C" ) );
    button_plusminus = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_plusminus" ) );
    button_multiply = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_multiply" ) );
    button_equal = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_equal" ) );
    button_dot = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_dot" ) );
    button_percent = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "button_percent" ) );

    txt1 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "txt1" ) );
    txt2 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "txt2" ) );

    label = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "label" ) );
    //gtk_text_view_1 = GTK_WIDGET ( gtk_builder_get_object( gbuilder, "gtk_text_view_1" ) );

    gtk_builder_connect_signals( gbuilder, NULL );  // w tym projekcie automatyczne podpiecie tylko on_window_main_destroy()

    g_object_unref ( G_OBJECT( gbuilder ) );     // mozna juz usunac gbuilder

    // preferujemy takie podpinanie funkcji do sygnalow emitowanych przez widgety
    g_signal_connect ( button_0, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );   // reczne podpiecie funkcji do sygnalu 'clicked' dla widgetu gtk_button_1
    g_signal_connect ( button_1, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_2, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_3, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_4, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_5, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_6, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_7, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_8, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );
    g_signal_connect ( button_9, "clicked", G_CALLBACK(on_gtk_digit__clicked), NULL );

    g_signal_connect ( button_plusminus, "clicked", G_CALLBACK(operation_clicked), NULL );
    g_signal_connect ( button_C, "clicked", G_CALLBACK(operation_clicked), NULL );
    g_signal_connect ( button_dot, "clicked", G_CALLBACK(operation_clicked), NULL );
    g_signal_connect ( button_percent, "clicked", G_CALLBACK(operation_clicked), NULL );

    g_signal_connect ( button_equal, "clicked", G_CALLBACK(equal_clicked), NULL );

    g_signal_connect ( button_plus, "clicked", G_CALLBACK(math_clicked), NULL );
    g_signal_connect ( button_minus, "clicked", G_CALLBACK(math_clicked), NULL );
    g_signal_connect ( button_multiply, "clicked", G_CALLBACK(math_clicked), NULL );
    g_signal_connect ( button_divide, "clicked", G_CALLBACK(math_clicked), NULL );

    g_signal_connect(gtk_window, "delete-event", G_CALLBACK(on_window_closed), NULL);


    // ustaw rozmiar glownego okna
    gtk_window_set_default_size ( GTK_WINDOW(gtk_window), 800, 650 );
    // ustaw okno w centrum glownego ekranu
    gtk_window_set_position ( GTK_WINDOW(gtk_window), GTK_WIN_POS_CENTER );

    // a jak zmienic tytul glownego okienka ?

    const char* cstr = windowTitle().c_str();

    gtk_window_set_title(GTK_WINDOW(gtk_window), cstr);


    //pokaz glowne okno
    gtk_widget_show ( gtk_window );

    gtk_main(); // w tej petli program okienkowy tkwi, dopuki go nie zakonczymy przyciskiem 'X'

// ========================================================================================================================

    // zakonczenie przeniesiono do on_window_main_destroy

    return 0;
}
