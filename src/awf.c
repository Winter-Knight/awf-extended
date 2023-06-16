/**
 * Forked  M/10/03/2020
 * Updated S/13/05/2023
 *
 * Copyright 2020-2023 | Fabrice Creuzot (luigifab) <code~luigifab~fr>
 * https://github.com/luigifab/awf-extended
 * https://www.luigifab.fr/gtk/awf-extended
 *
 * Forked from
 *  Copyright 2011-2017 | Valère Monseur (valr) <valere.monseur~ymail~com>
 *  https://github.com/valr/awf
 *
 * Forked from
 *  AWF is originally based on the code from The Widget Factory
 *  created by Richard Stellingwerff <remenic~gmail~com>
 *
 * This program is free software, you can redistribute it or modify
 * it under the terms of the GNU General Public License (GPL) as published
 * by the free software foundation, either version 3 of the license, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but without any warranty, without even the implied warranty of
 * merchantability or fitness for a particular purpose. See the
 * GNU General Public License (GPL) for more details.
 *
 *
 * Translations update:
 *  xgettext --keyword=_app -d awf -o src/awf.pot -k_ -s src/awf.c
 *  msgmerge src/po/fr.po src/awf.pot -o src/po/fr.po
 *  msgfmt src/po/fr.po -o src/fr/LC_MESSAGES/awf.mo
 *
 * Tested with build.sh (via VirtualBox 7.0) with:
 *  Debian Testing 64               (1536 MB) GTK 2.24/3.24/4.8  + GLIB 2.74 + Pango 1.50
 *  Fedora Rawhide 64               (1536 MB) GTK 2.24/3.24/4.11 + GLIB 2.76 + Pango 1.50
 *  Ubuntu 23.04 Lunar Lobster 64   (2560 MB) GTK 2.24/3.24/4.10 + GLIB 2.76 + Pango 1.50
 *  Ubuntu 22.10 Kinetic Kudu 64    (2560 MB) GTK 2.24/3.24/4.8 + GLIB 2.74 + Pango 1.50
 *  Ubuntu 22.04 Jammy Jellyfish 64 (2560 MB) GTK 2.24/3.24/4.6 + GLIB 2.72 + Pango 1.50
 *  Ubuntu 21.10 Impish Indri 64    (2560 MB) GTK 2.24/3.24/4.4 + GLIB 2.68 + Pango 1.48
 *  Ubuntu 21.04 Hirsute Hippo 64   (1536 MB) GTK 2.24/3.24/4.0 + GLIB 2.68 + Pango 1.48
 *  Ubuntu 17.04 Zesty Zapus 32         (1536 MB) GTK 2.24/3.22 + GLIB 2.52 + Pango 1.40
 *  Ubuntu 16.10 Yakkety Yak 32         (1536 MB) GTK 2.24/3.20 + GLIB 2.50 + Pango 1.40
 *  Ubuntu 16.04 Xenial Xerus 32        (1536 MB) GTK 2.24/3.18 + GLIB 2.48 + Pango 1.38
 *  Ubuntu 15.10 Wily Werewolf 32       (1024 MB) GTK 2.24/3.16 + GLIB 2.46 + Pango 1.36
 *  Ubuntu 15.04 Vivid Vervet 32        (1024 MB) GTK 2.24/3.14 + GLIB 2.44 + Pango 1.36
 *  Ubuntu 14.10 Utopic Unicorn 32      (1024 MB) GTK 2.24/3.12 + GLIB 2.42 + Pango 1.36
 *  Ubuntu 14.04 Trusty Tahr 32         (1024 MB) GTK 2.24/3.10 + GLIB 2.40 + Pango 1.36
 *  Ubuntu 13.10 Saucy Salamander 32    (1024 MB) GTK 2.24/3.8  + GLIB 2.38 + Pango 1.32
 *  Ubuntu 13.04 Raring Ringtail 32     (1024 MB) GTK 2.24/3.6  + GLIB 2.36 + Pango 1.32
 *  Ubuntu 12.04 Precise Pangolin 32    (1024 MB) GTK 2.24/3.4  + GLIB 2.32 + Pango 1.30
 *  Ubuntu 11.10 Oneiric Ocelot 32      (1024 MB) GTK 2.24/3.2  + GLIB 2.30 + Pango 1.29
 *  Ubuntu 11.04 Natty Narwhal 32       (1024 MB) GTK 2.24/3.0  + GLIB 2.28 + Pango 1.28
 */

#include <glib/gi18n.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>
#include <gtk/gtkunixprint.h>
#include <gdk/gdk.h>
#include <time.h>
#include <getopt.h>

#if GLIB_CHECK_VERSION (2,30,0)
	#include <glib-unix.h>
#endif

#if GTK_CHECK_VERSION (3,0,0)
	#define GETTEXT_PACKAGE g_strdup_printf ("awf-gtk%d", GTK_MAJOR_VERSION)
	#define gtk_major_version gtk_get_major_version ()
	#define gtk_minor_version gtk_get_minor_version ()
	#define gtk_micro_version gtk_get_micro_version ()
	#define BOXH (gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0))
	#define BOXV (gtk_box_new (GTK_ORIENTATION_VERTICAL, 0))
	#define SEPH (gtk_separator_new (GTK_ORIENTATION_HORIZONTAL))
	#define SEPV (gtk_separator_new (GTK_ORIENTATION_VERTICAL))
	#define PANEH (gtk_paned_new (GTK_ORIENTATION_HORIZONTAL))
	#define PANEV (gtk_paned_new (GTK_ORIENTATION_VERTICAL))
#else
	#define GETTEXT_PACKAGE "awf-gtk2"
	#define BOXH (gtk_hbox_new (FALSE, 0))
	#define BOXV (gtk_vbox_new (FALSE, 0))
	#define SEPH (gtk_hseparator_new ())
	#define SEPV (gtk_vseparator_new ())
	#define PANEH (gtk_hpaned_new ())
	#define PANEV (gtk_vpaned_new ())
	#define GDK_KEY_F1 0xffbe
	#define GDK_KEY_F2 0xffbf
	#define GDK_KEY_F3 0xffc0
	#define GDK_KEY_F4 0xffc1
	#define GDK_KEY_F5 0xffc2
	#define GDK_KEY_F6 0xffc3
	#define GDK_KEY_F7 0xffc4
	#define GDK_KEY_F8 0xffc5
	#define GDK_KEY_F9 0xffc6
	#define GDK_KEY_F10 0xffc7
	#define GDK_KEY_F11 0xffc8
	#define GDK_KEY_F12 0xffc9
	#define GDK_KEY_Delete 0xffff
	#define GDK_KEY_KP_Delete 0xff9f
	#define GDK_KEY_BackSpace 0xff08
#endif

#define AWF_OPEN "<AWF>/Test/Open"
#define AWF_RECE "<AWF>/Test/Recent"
#define AWF_CALE "<AWF>/Test/Calendar"
#define AWF_SCAT "<AWF>/Test/ScalesTop"
#define AWF_SCAB "<AWF>/Test/ScalesBottom"
#define AWF_SCAR "<AWF>/Test/ScalesRight"
#define AWF_SCAL "<AWF>/Test/ScalesLeft"
#define AWF_SAVE "<AWF>/Test/Save"
#define AWF_REFR "<AWF>/Test/Refresh"
#define AWF_PROP "<AWF>/Test/Properties"
#define AWF_PRSE "<AWF>/Test/PrintSetup"
#define AWF_PRIN "<AWF>/Test/Print"
#define AWF_ABOU "<AWF>/Test/About"
#define AWF_MCUT "<AWF>/Test/More/Cut"
#define AWF_MCOP "<AWF>/Test/More/Copy"
#define AWF_MPAS "<AWF>/Test/More/Past"
#define AWF_CLOS "<AWF>/Test/Close"
#define AWF_QUIT "<AWF>/Test/Quit"

#define AWF_ACCEL_OPEN "<Control>O"
#define AWF_ACCEL_RECE NULL
#define AWF_ACCEL_CALE NULL
#define AWF_ACCEL_SCAT NULL
#define AWF_ACCEL_SCAB NULL
#define AWF_ACCEL_SCAR NULL
#define AWF_ACCEL_SCAL NULL
#define AWF_ACCEL_SAVE "<Control>S"
#define AWF_ACCEL_REFR "F5"
#define AWF_ACCEL_PROP "<Alt>Return"
#define AWF_ACCEL_PRSE "<Control><Shift>P"
#define AWF_ACCEL_PRIN "<Control>P"
#define AWF_ACCEL_ABOU "F1"
#define AWF_ACCEL_MCUT "<Control>X"
#define AWF_ACCEL_MCOP "<Control>C"
#define AWF_ACCEL_MPAS "<Control>V"
#define AWF_ACCEL_CLOS "<Control>W"
#define AWF_ACCEL_QUIT "<Control>Q"

// https://stackoverflow.com/a/10018581/2980105
#define _app(String) dgettext (GETTEXT_PACKAGE, String)
#define _gtk(String) dgettext (g_strdup_printf ("gtk%d0", GTK_MAJOR_VERSION), String)

// global variables
static GSList *list_system_theme = NULL;
static GSList *list_user_theme = NULL;
static GtkWidget *window = NULL, *statusbar = NULL;
static GtkWidget *volume1 = NULL, *volume2 = NULL;
static GtkWidget *progressbar1 = NULL, *progressbar2 = NULL, *progressbar3 = NULL, *progressbar4 = NULL;
static GtkWidget *scale1 = NULL, *scale2 = NULL, *scale3 = NULL, *scale4 = NULL, *scale5 = NULL, *scale6 = NULL;
static GtkWidget *levelbar1 = NULL, *levelbar2 = NULL, *levelbar3 = NULL, *levelbar4 = NULL;
static GtkWidget *levelbar5 = NULL, *levelbar6 = NULL, *levelbar7 = NULL, *levelbar8 = NULL;
static GtkWidget *notebook1 = NULL, *notebook2 = NULL, *notebook3 = NULL, *notebook4 = NULL;
static GtkWidget *current_menuitem = NULL;
static int current_direction = GTK_TEXT_DIR_NONE;
static gchar *current_theme  = "auto";
static gchar *opt_screenshot = NULL;
static gboolean opt_startspinner   = TRUE;
static gboolean allow_update_theme = TRUE;
static gboolean must_save_accels   = FALSE;

// global functions
static void quit ();
static GSList* awf_load_theme (gchar *directory);
static int awf_compare_theme (gconstpointer theme1, gconstpointer theme2);
static void update_text_direction (int direction);
static void update_theme (gchar *new_theme);
static void update_statusbar (gchar *message);
static void update_values (GtkRange *range);
static void update_widgets ();
static void update_marks (GtkScale *scale, gboolean value, int position);
static gboolean on_sighup ();
static gboolean take_screenshot ();
static void create_window (gpointer app);
static void create_widgets (GtkWidget *root);
static void add_to (GtkBox *box, GtkWidget *widget, gboolean fill, gboolean expand, guint padding, guint spacing);
static void create_toolbar (GtkWidget *root);
static void create_combos_entries (GtkWidget *root);
static void create_spinbuttons (GtkWidget *root);
static void create_checkbuttons (GtkWidget *root);
static void create_radiobuttons (GtkWidget *root);
static void create_otherbuttons (GtkWidget *root1, GtkWidget *root2, GtkWidget *root3, GtkWidget *root4, GtkWidget *root5);
static void create_progressbars (GtkWidget *root1, GtkWidget *root2, GtkWidget *root3, GtkWidget *root4);
static void create_labels (GtkWidget *root);
static void create_spinners (GtkWidget *root);
static void create_expander (GtkWidget *root);
static void create_frames (GtkWidget *root1, GtkWidget *root2);
static void create_notebooks (GtkWidget *root1, GtkWidget *root2);
static void create_notebook_tab (GtkWidget *notebook, gchar *text, gboolean close);
static void create_treview (GtkWidget *root);
static GtkWidget* create_horizontal_scale (gdouble value, gboolean draw, gboolean inverted, int position);
static GtkWidget* create_vertical_scale (gdouble value, gboolean draw, gboolean inverted, int position);
#if GTK_CHECK_VERSION (4,0,0)
static void closedialog (GtkDialog *dialog);
static void activate_action (GSimpleAction *action, GVariant *parameter, gpointer data);
static void create_traditional_menubar (GtkApplication *app, GMenu *root);
static GMenuItem* create_menuitem (GtkApplication *app, GMenu *menu, gchar *text, gchar *accel, gchar *keymap, GCallback function);
static void accels_change (GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state);
static void accels_save ();
#else
static void create_traditional_menubar (GtkWidget *root);
static GtkWidget* create_menu (GtkWidget *root, gchar *text);
static GtkWidget* create_menuitem_tearoff (GtkWidget *menu);
static GtkWidget* create_menuitem_check (GtkWidget *menu, gchar *text, gboolean checked, gboolean inconsistent, gboolean disabled);
static GtkWidget* create_menuitem_radio (GtkWidget *menu, gchar *text, gboolean checked, gboolean inconsistent, gboolean disabled, GSList *group);
static GtkWidget* create_menuitem (GtkWidget *menu, gchar *text, gboolean disabled, gchar *accel, gchar *keymap, GCallback function);
static void accels_load ();
static void accels_select (GtkWidget *widget);
static void accels_deselect (GtkWidget *widget);
static void accels_change (GtkWidget *widget, GdkEventKey *event);
static void accels_save ();
#endif
static void dialog_open ();
static void dialog_recent ();
static void dialog_save ();
static void dialog_message ();
static void dialog_page_setup ();
static void dialog_print ();
static void dialog_about ();
static void dialog_calendar ();
static void dialog_scales_top ();
static void dialog_scales_bottom ();
static void dialog_scales_right ();
static void dialog_scales_left ();
static void dialog_scales (int position);
#if GTK_CHECK_VERSION (4,0,0)
static gboolean on_scrolltabs (GtkEventControllerScroll *event, double dx, double dy, GtkWidget *widget);
#elif GTK_CHECK_VERSION (3,4,0)
static gboolean on_scrolltabs (GtkWidget *widget, GdkEventScroll *event);
#endif


// run run run

int main (int argc, gchar **argv) {

	int opt = 0, status = 0;
	GSList *iterator = NULL;

	// load available themes
	// @todo replace GSLists?
	list_system_theme = awf_load_theme ("/usr/share/themes");
	list_system_theme = g_slist_sort (list_system_theme, (GCompareFunc) awf_compare_theme);

	gchar *directory = g_build_path ("/", g_getenv ("HOME"), ".themes", NULL);
	list_user_theme = awf_load_theme (directory);
	list_user_theme = g_slist_sort (list_user_theme, (GCompareFunc) awf_compare_theme);
	g_free (directory);

	// locale
	setlocale (LC_ALL, "");
	if (g_file_test ("/usr/share/locale", G_FILE_TEST_IS_DIR))
		bindtextdomain (GETTEXT_PACKAGE, "/usr/share/locale");
	bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
	textdomain (GETTEXT_PACKAGE);

	// init
	static struct option long_options[] = {
		{"ltr", no_argument, NULL, 'y'},
		{"rtl", no_argument, NULL, 'z'},
		{NULL, 0, NULL, 0}
	};

	while ((opt = getopt_long (argc, argv, "vs:nt:lh", long_options, NULL)) != -1) {
		switch (opt) {
			case 'v':
				g_printf ("%s\n", VERSION);
				return status;
			case 's':
				opt_screenshot = optarg;
				break;
			case 'n':
				opt_startspinner = FALSE;
			case 't':
				if (g_slist_find_custom (list_system_theme, optarg, &awf_compare_theme) ||
					g_slist_find_custom (list_user_theme, optarg, &awf_compare_theme))
					current_theme = (gchar*) optarg;
				break;
			case 'l':
				for (iterator = list_system_theme; iterator; iterator = iterator->next)
					g_printf ("%s\n", (gchar*) iterator->data);
				for (iterator = list_user_theme; iterator; iterator = iterator->next)
					g_printf ("%s\n", (gchar*) iterator->data);
				return status;
			case 'y':
				current_direction = GTK_TEXT_DIR_LTR;
				break;
			case 'z':
				current_direction = GTK_TEXT_DIR_RTL;
				break;
			case 'h':
			default:
				g_printf ("%s\n\n  %s %s\n  %s %s\n  %s %s\n  %s %s\n  %s %s\n  %s %s\n  %s %s\n\n%s\n%s\n",
					g_strdup_printf (_app("A widget factory %s - GTK %d.%d"), VERSION, GTK_MAJOR_VERSION, GTK_MINOR_VERSION),
					"-v            ", _app("Show version number."),
					"-l            ", _app("List available themes."),
					"-n            ", _app("Don't start spinners."),
					"-t <theme>    ", _app("Run with the specified theme."),
					"-s <filename> ", g_strdup_printf (_app("Run and save a png screenshot on %s."), "SIGHUP"),
					"--ltr         ", _app("Start with text from left to right (Left-To-Right)."),
					"--rtl         ", _app("Start with text from right to left (Right-To-Left)."),
					g_strdup_printf (_app("compiled with gtk %d.%d.%d and glib %d.%d.%d and pango %s"),
						GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
						GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION,
						PANGO_VERSION_STRING),
					g_strdup_printf (_app(" started with gtk %d.%d.%d and glib %d.%d.%d and pango %s"),
						gtk_major_version, gtk_minor_version, gtk_micro_version,
						glib_major_version, glib_minor_version, glib_micro_version,
						pango_version_string ())
				);
				return status;
		}
	}

	// create and show window
	#if GLIB_CHECK_VERSION (2,30,0)
		g_unix_signal_add (SIGHUP, on_sighup, NULL); // glib >= 2.30
	#endif

	#if GTK_CHECK_VERSION (4,0,0)
		GtkApplication *app;
		app = gtk_application_new ("org.gtk.awf4", G_APPLICATION_NON_UNIQUE);
		g_signal_connect (app, "activate", G_CALLBACK (create_window), NULL);
		g_application_register (G_APPLICATION (app), NULL, NULL);
		status = g_application_run (G_APPLICATION (app), 0, NULL); // @todo (app, argc, argv)
	#elif GTK_CHECK_VERSION (3,4,0)
		GtkApplication *app;
		app = gtk_application_new ("org.gtk.awf3", G_APPLICATION_NON_UNIQUE);
		g_signal_connect (app, "activate", G_CALLBACK (create_window), NULL);
		status = g_application_run (G_APPLICATION (app), 0, NULL); // @todo (app, argc, argv)
	#else
		gtk_init (&argc, &argv);
		create_window (NULL);
	#endif

	return status;
}

static void quit () {
	accels_save ();
	exit (0);
}

static GSList* awf_load_theme (gchar *directory) {

	GSList *list = NULL;
	g_return_val_if_fail (directory != NULL, NULL);

	if (g_file_test (directory, G_FILE_TEST_IS_DIR)) {

		GError *error = NULL;
		GDir *dir = g_dir_open (directory, 0, &error);

		if (dir) {
			gchar *theme  = g_strdup (g_dir_read_name (dir));
			gchar *gtkdir = g_strdup_printf ("gtk-%d.0", GTK_MAJOR_VERSION);

			while (theme) {
				gchar *theme_path = g_build_path ("/", directory, g_strstrip (theme), NULL);

				if (g_file_test (theme_path, G_FILE_TEST_IS_DIR)) {
					gchar *theme_subpath = g_build_path ("/", theme_path, gtkdir, NULL);
					if (g_file_test (theme_subpath, G_FILE_TEST_IS_DIR))
						list = g_slist_prepend (list, theme);
					g_free (theme_subpath);
				}

				g_free (theme_path);
				theme = g_strdup (g_dir_read_name (dir));
			}

			g_dir_close (dir);
			g_free (gtkdir);
			g_free (theme);
		}

		if (error) {
			g_fprintf (stderr, "unable to open directory: %s (%s)\n", directory, error->message);
			g_error_free (error);
		}
	}

	if (list)
		list = g_slist_reverse (list);

	return list;
}

static int awf_compare_theme (gconstpointer theme1, gconstpointer theme2) {
	return g_strcmp0 ((gchar*) theme1, (gchar*) theme2);
}

static void update_text_direction (int direction) {

	// we must ignore the activate signal when menubar is created
	if (!allow_update_theme)
		return;

	gboolean toggle = gtk_notebook_get_scrollable (GTK_NOTEBOOK (notebook1));

	if (((direction == GTK_TEXT_DIR_LTR) || (direction == 1)) && (gtk_widget_get_direction (window) != GTK_TEXT_DIR_LTR)) {

		current_direction = GTK_TEXT_DIR_LTR;
		gtk_widget_set_default_direction (current_direction);

		#if GTK_CHECK_VERSION (3,20,0) && !GTK_CHECK_VERSION (4,0,0)
			gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook3), GTK_POS_LEFT);
			gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook4), GTK_POS_RIGHT);
		#endif

		gtk_scale_clear_marks (GTK_SCALE (scale5));
		update_marks (GTK_SCALE (scale5), toggle, GTK_POS_LEFT);

		gtk_scale_clear_marks (GTK_SCALE (scale6));
		update_marks (GTK_SCALE (scale6), toggle, GTK_POS_RIGHT);
	}
	else if (((direction == GTK_TEXT_DIR_RTL) || (direction == 2)) && (gtk_widget_get_direction (window) != GTK_TEXT_DIR_RTL)) {

		#if GTK_CHECK_VERSION (3,20,0) && !GTK_CHECK_VERSION (4,0,0)
			gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook3), GTK_POS_RIGHT);
			gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook4), GTK_POS_LEFT);
		#endif

		gtk_scale_clear_marks (GTK_SCALE (scale5));
		update_marks (GTK_SCALE (scale5), toggle, GTK_POS_RIGHT);

		gtk_scale_clear_marks (GTK_SCALE (scale6));
		update_marks (GTK_SCALE (scale6), toggle, GTK_POS_LEFT);

		current_direction = GTK_TEXT_DIR_RTL;
		gtk_widget_set_default_direction (current_direction);
	}
}

static void update_theme (gchar *new_theme) {

	// we must ignore the activate signal when menubar is created
	if (!allow_update_theme)
		return;

	if (strcmp ((gchar*) new_theme, "refresh") == 0) {

		gchar *default_theme = "None";
		if (g_slist_find_custom (list_system_theme, "Default", &awf_compare_theme))
			default_theme = "Default";
		else if (g_slist_find_custom (list_system_theme, "Raleigh", &awf_compare_theme))
			default_theme = "Raleigh";

		if (default_theme) {

			g_object_set (gtk_settings_get_default (), "gtk-theme-name", default_theme, NULL);
			g_usleep (G_USEC_PER_SEC / 2);
			g_object_set (gtk_settings_get_default (), "gtk-theme-name", current_theme, NULL);

			// @todo force reload of ".config/gtk*/gtk.css"

			gchar *text = g_strdup_printf (_app("Theme %s reloaded."), current_theme);
			update_statusbar (text);
			g_free (text);

			if (opt_screenshot)
				g_timeout_add_seconds (1, take_screenshot, NULL);
		}
	}
	else if (strcmp ((gchar*) new_theme, "auto") == 0) {
		g_object_get (gtk_settings_get_default (), "gtk-theme-name", &current_theme, NULL);
	}
	else if (strcmp ((gchar*) current_theme, (gchar*) new_theme) != 0) {

		g_object_set (gtk_settings_get_default (), "gtk-theme-name", new_theme,  NULL);
		g_object_get (gtk_settings_get_default (), "gtk-theme-name", &current_theme, NULL);
		//g_settings_set_string (g_settings_new ("org.mate.Marco.general"), "theme", (gchar*) current_theme);

		#if GTK_CHECK_VERSION (4,0,0)
			gtk_window_set_default_size (GTK_WINDOW (window), 50, 50);
		#else
			gtk_window_resize (GTK_WINDOW (window), 50, 50);
		#endif

		gchar *text = g_strdup_printf (_app("Theme %s loaded."), current_theme);
		update_statusbar (text);
		g_free (text);
	}
}

static void update_statusbar (gchar *message) {

	if (!statusbar)
		return;

	char buffer[12];
	time_t rawtime;

	time (&rawtime);
	strftime (buffer, sizeof buffer, "%T", localtime (&rawtime));

	gchar *text = g_strdup_printf ("%s - %s", buffer, message);
	gtk_statusbar_push (GTK_STATUSBAR (statusbar), gtk_statusbar_get_context_id (GTK_STATUSBAR (statusbar), "gné"), text);
	g_free (text);
}

static void update_values (GtkRange *range) {

	double value = gtk_range_get_value (range);

	// range (0..1)
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar1), value / 100.0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar2), value / 100.0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar3), value / 100.0);
	gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar4), value / 100.0);

	#if GTK_CHECK_VERSION (3,6,0)
		// range (0..1)
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar1), value / 100.0);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar2), value / 100.0);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar5), value / 100.0);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar6), value / 100.0);
		// range (0..5)
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar3), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar3)));
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar4), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar4)));
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar7), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar7)));
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar8), value / 100.0 * gtk_level_bar_get_max_value (GTK_LEVEL_BAR (levelbar8)));
	#endif

	// range (0..1)
	gtk_scale_button_set_value (GTK_SCALE_BUTTON (volume1), value / 100.0);

	// range (0..100)
	if (scale1 != (GtkWidget*) range) gtk_range_set_value (GTK_RANGE (scale1), value);
	if (scale2 != (GtkWidget*) range) gtk_range_set_value (GTK_RANGE (scale2), value);
	if (scale3 != (GtkWidget*) range) gtk_range_set_value (GTK_RANGE (scale3), value);
	if (scale4 != (GtkWidget*) range) gtk_range_set_value (GTK_RANGE (scale4), value);
	if (scale5 != (GtkWidget*) range) gtk_range_set_value (GTK_RANGE (scale5), value);
	if (scale6 != (GtkWidget*) range) gtk_range_set_value (GTK_RANGE (scale6), value);

	#if !GTK_CHECK_VERSION (3,0,0)
		if (gtk_progress_bar_get_text (GTK_PROGRESS_BAR (progressbar1))) {
			gchar *text = g_strdup_printf ("%i %%", (int) value);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar1), text);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar3), text);
			g_free (text);
		}
	#endif
}

static void update_widgets () {

	gboolean toggle = gtk_notebook_get_scrollable (GTK_NOTEBOOK (notebook1));

	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook1), !toggle);
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook2), !toggle);
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook3), !toggle);
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook4), !toggle);

	gtk_widget_set_sensitive (scale2, toggle);
	gtk_widget_set_sensitive (scale4, toggle);
	gtk_widget_set_sensitive (scale6, toggle);

	gtk_widget_set_sensitive (progressbar2, toggle);
	gtk_widget_set_sensitive (progressbar4, toggle);

	#if GTK_CHECK_VERSION (3,6,0)
		gtk_widget_set_sensitive (levelbar2, toggle);
		gtk_widget_set_sensitive (levelbar4, toggle);
		gtk_widget_set_sensitive (levelbar6, toggle);
		gtk_widget_set_sensitive (levelbar8, toggle);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar1), !toggle);
		gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar2), !toggle);
		gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar3), !toggle);
		gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR (progressbar4), !toggle);
	#else
		if (toggle) {
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar1), NULL);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar2), NULL);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar3), NULL);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar4), NULL);
		}
		else {
			gchar *text = g_strdup_printf ("%i %%", (int) gtk_range_get_value (GTK_RANGE (scale1)));
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar1), text);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar2), text);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar3), text);
			gtk_progress_bar_set_text (GTK_PROGRESS_BAR (progressbar4), text);
			g_free (text);
		}
	#endif

	gtk_scale_clear_marks (GTK_SCALE (scale5));
	update_marks (GTK_SCALE (scale5), !toggle, GTK_POS_LEFT);

	gtk_scale_clear_marks (GTK_SCALE (scale6));
	update_marks (GTK_SCALE (scale6), !toggle, GTK_POS_RIGHT);
}

static void update_marks (GtkScale *scale, gboolean value, int position) {

	if (value) {
		gtk_scale_add_mark (scale,   0, position, NULL);
		gtk_scale_add_mark (scale,  25, position, "25");
		gtk_scale_add_mark (scale,  50, position, "50");
		gtk_scale_add_mark (scale,  75, position, "75");
		gtk_scale_add_mark (scale, 100, position, NULL);
	}
	else {
		gtk_scale_add_mark (scale,   0, position, NULL);
		gtk_scale_add_mark (scale,  25, position, NULL);
		gtk_scale_add_mark (scale,  50, position, NULL);
		gtk_scale_add_mark (scale,  75, position, NULL);
		gtk_scale_add_mark (scale, 100, position, NULL);
	}
}

static gboolean on_sighup () {

	update_theme ("refresh");

	#if !defined (G_SOURCE_CONTINUE)
		return TRUE; // glib < 2.32
	#else
		return G_SOURCE_CONTINUE;
	#endif
}

static gboolean take_screenshot () {

	GdkPixbuf *image = NULL;
	int width = 0, height = 0;

	#if GTK_CHECK_VERSION (4,0,0)
		// @todo
	#elif GTK_CHECK_VERSION (3,0,0)
		GdkWindow *root = gtk_widget_get_window (window);
		gtk_window_get_size (GTK_WINDOW (window), &width, &height);
		image = gdk_pixbuf_get_from_window (root, 0, 0, width, height);
	#else
		GdkWindow *root = gtk_widget_get_window (window);
		gtk_window_get_size (GTK_WINDOW (window), &width, &height);
		image = gdk_pixbuf_get_from_drawable (NULL, root, gdk_colormap_get_system (), 0, 0, 0, 0, width, height);
	#endif

	if (image) {
		gdk_pixbuf_save (image, opt_screenshot, "png", NULL, "compression", "9", NULL);
		g_object_unref (image);
 		gchar *text = g_strdup_printf (_app("Theme reloaded, then screenshot saved (%s)."), opt_screenshot);
		update_statusbar (text);
		g_free (text);
	}

	return FALSE;
}


// layout and widgets

static void create_window (gpointer app) {

	GtkWidget *vbox_window, *toolbar, *widgets;
	gchar *text;

	// window
	#if GTK_CHECK_VERSION (3,4,0)
		window = gtk_application_window_new (GTK_APPLICATION (app));
	#else
		window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	#endif

	gtk_window_set_icon_name (GTK_WINDOW (window), GETTEXT_PACKAGE);
	text = g_strdup_printf (_app("A widget factory %s - GTK %d.%d"), VERSION, GTK_MAJOR_VERSION, GTK_MINOR_VERSION);
	gtk_window_set_title (GTK_WINDOW (window), text);
	g_free (text);

	update_theme (current_theme);
	allow_update_theme = FALSE;
	if (current_direction == GTK_TEXT_DIR_NONE)
		current_direction = gtk_widget_get_default_direction ();

	// layout
	vbox_window = BOXV;
	#if GTK_CHECK_VERSION (4,0,0)
		gtk_window_set_child (GTK_WINDOW (window), vbox_window);
	#else
		gtk_container_add (GTK_CONTAINER (window), vbox_window);
	#endif

		#if GTK_CHECK_VERSION (4,0,0)
			GMenu *gmm;
			gmm = g_menu_new ();
			create_traditional_menubar (app, gmm);
			gtk_application_set_menubar (app, G_MENU_MODEL (gmm));
			gtk_application_window_set_show_menubar (GTK_APPLICATION_WINDOW (window), TRUE);

			toolbar = BOXH;
			add_to (GTK_BOX (vbox_window), toolbar, FALSE, FALSE, 0, 0);
			create_toolbar (toolbar);
		#else
			GtkWidget *menubar;
			menubar = gtk_menu_bar_new ();
			create_traditional_menubar (menubar);
			add_to (GTK_BOX (vbox_window), menubar, FALSE, FALSE, 0, 0);

			toolbar = gtk_toolbar_new ();
			add_to (GTK_BOX (vbox_window), toolbar, FALSE, FALSE, 0, 0);
			create_toolbar (toolbar);
		#endif

		widgets = BOXV;
		add_to (GTK_BOX (vbox_window), widgets, TRUE, TRUE, 0, 0);
			create_widgets (widgets);

		statusbar = gtk_statusbar_new ();
		add_to (GTK_BOX (vbox_window), statusbar, FALSE, FALSE, 0, 0);

		text = g_strdup_printf (_app("Theme %s loaded."), current_theme);
		update_statusbar (text);
		g_free (text);

	// go
	allow_update_theme = TRUE;
	update_text_direction (current_direction);

	g_signal_connect (window, "destroy", G_CALLBACK (quit), NULL);

	#if GTK_CHECK_VERSION (4,0,0)
		// gtk-can-change-accels for GTK 4.x
		//GtkEventController *event;
		//event = gtk_event_controller_key_new ();
		//g_signal_connect (event, "key-released", G_CALLBACK (accels_change), window);
		//gtk_widget_add_controller (window, event);
		gtk_widget_add_css_class (toolbar, "primary-toolbar");
		gtk_widget_set_visible (window, TRUE);
	#elif GTK_CHECK_VERSION (3,4,0)
		gtk_style_context_add_class (gtk_widget_get_style_context (toolbar), "primary-toolbar");
		gtk_widget_show_all (window);
	#elif GTK_CHECK_VERSION (3,0,0)
		gtk_style_context_add_class (gtk_widget_get_style_context (toolbar), "primary-toolbar");
		gtk_widget_show_all (window);
		gtk_main ();
	#else
		gtk_widget_show_all (window);
		gtk_main ();
	#endif
}

static void create_widgets (GtkWidget *root) {

	GtkWidget *hbox_columns = BOXH;
	GtkWidget *vbox_column1 = BOXV, *vbox_combo_entry = BOXV, *hbox_spin = BOXH, *hbox_check_radio = BOXH, *vbox_check = BOXV, *vbox_radio = BOXV;
	GtkWidget *vbox_column2 = BOXV, *vbox_buttons = BOXV, *hbox_btns1 = BOXH, *hbox_btns2 = BOXH, *hbox_btns3 = BOXH, *hbox_btns4 = BOXH;
	GtkWidget *vbox_column3 = BOXV, *vbox_progressbar1 = BOXV, *vbox_progressbar2 = BOXV, *hbox_progressbar1 = BOXH, *hbox_progressbar2 = BOXH;
	GtkWidget *vbox_column4 = BOXV, *vbox_others = BOXV, *hbox_label = BOXH, *hbox_spinner = BOXH;
	GtkWidget *vpane = PANEV, *hpane1 = PANEH, *hpane2 = PANEH;
	GtkWidget *hbox_frame1 = BOXH, *hbox_frame2 = BOXH, *hbox_notebook1 = BOXH, *hbox_notebook2 = BOXH;

	// columns layout
	add_to (GTK_BOX (root), hbox_columns, TRUE, TRUE, 0, 0);

		// column 1
		add_to (GTK_BOX (hbox_columns), vbox_column1, TRUE, TRUE, 5, 0);
			add_to (GTK_BOX (vbox_column1), vbox_combo_entry, FALSE, TRUE, 5, 3);
				create_combos_entries (vbox_combo_entry);
			add_to (GTK_BOX (vbox_column1), hbox_spin, FALSE, FALSE, 5, 0);
				create_spinbuttons (hbox_spin);
			add_to (GTK_BOX (vbox_column1), hbox_check_radio, FALSE, TRUE, 5, 0);
				add_to (GTK_BOX (hbox_check_radio), vbox_check, TRUE, TRUE, 0, 0);
					create_checkbuttons (vbox_check);
				add_to (GTK_BOX (hbox_check_radio), vbox_radio, TRUE, TRUE, 0, 0);
					create_radiobuttons (vbox_radio);
		add_to (GTK_BOX (hbox_columns), SEPV, FALSE, FALSE, 0, 0);

		// column 2
		add_to (GTK_BOX (hbox_columns), vbox_column2, TRUE, TRUE, 5, 0);
			add_to (GTK_BOX (vbox_column2), vbox_buttons, FALSE, TRUE, 5, 3);
			add_to (GTK_BOX (vbox_column2), hbox_btns1, FALSE, FALSE, 5, 3);
			add_to (GTK_BOX (vbox_column2), hbox_btns2, FALSE, FALSE, 5, 3);
			add_to (GTK_BOX (vbox_column2), hbox_btns3, FALSE, FALSE, 5, 3);
			add_to (GTK_BOX (vbox_column2), hbox_btns4, FALSE, FALSE, 5, 3);
				create_otherbuttons (vbox_buttons, hbox_btns1, hbox_btns2, hbox_btns3, hbox_btns4);
		add_to (GTK_BOX (hbox_columns), SEPV, FALSE, FALSE, 0, 0);

		// column 3
		add_to (GTK_BOX (hbox_columns), vbox_column3, TRUE, TRUE, 5, 0);
			add_to (GTK_BOX (vbox_column3), vbox_progressbar1, FALSE, TRUE, 6, 10);
			add_to (GTK_BOX (vbox_column3), hbox_progressbar1, FALSE, FALSE, 5, 10);
			add_to (GTK_BOX (vbox_column3), hbox_progressbar2, FALSE, FALSE, 5, 10);
			add_to (GTK_BOX (vbox_column3), vbox_progressbar2, FALSE, TRUE, 5, 10);
				create_progressbars (vbox_progressbar1, hbox_progressbar1, hbox_progressbar2, vbox_progressbar2);
		add_to (GTK_BOX (hbox_columns), SEPV, FALSE, FALSE, 0, 0);

		// column 4
		add_to (GTK_BOX (hbox_columns), vbox_column4, TRUE, TRUE, 5, 0);
			add_to (GTK_BOX (vbox_column4), vbox_others, FALSE, TRUE, 5, 3);
				create_treview (vbox_others);
				add_to (GTK_BOX (vbox_others), hbox_label, FALSE, TRUE, 5, 0);
					create_labels (hbox_label);
				add_to (GTK_BOX (vbox_others), hbox_spinner, FALSE, TRUE, 5, 0);
					create_spinners (hbox_spinner);
				create_expander (vbox_others);

	add_to (GTK_BOX (root), SEPH, FALSE, FALSE, 0, 0);

	// paned layout
	add_to (GTK_BOX (root), vpane, TRUE, TRUE, 0, 0);

		#if GTK_CHECK_VERSION (4,0,0)
			gtk_paned_set_start_child (GTK_PANED (vpane), hpane1);
			gtk_paned_set_shrink_start_child (GTK_PANED (vpane), FALSE);
		#else
			gtk_paned_pack1 (GTK_PANED (vpane), hpane1, TRUE, FALSE);
		#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_frame1), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_frame1), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_size_request (hbox_frame1, -1, 50);
				gtk_widget_set_margin_start (hbox_frame1, 10);
				gtk_widget_set_margin_end (hbox_frame1, 10);
				gtk_widget_set_margin_top (hbox_frame1, 10);
				gtk_widget_set_margin_bottom (hbox_frame1, 10);
			#else
				gtk_widget_set_size_request (hbox_frame1, -1, 70);
				gtk_container_set_border_width (GTK_CONTAINER (hbox_frame1), 10);
			#endif
			#if GTK_CHECK_VERSION (4,0,0)
				gtk_paned_set_start_child (GTK_PANED (hpane1), hbox_frame1);
				gtk_paned_set_resize_start_child (GTK_PANED (hpane1), FALSE);
				gtk_paned_set_shrink_start_child (GTK_PANED (hpane1), FALSE);
			#else
				gtk_paned_add1 (GTK_PANED (hpane1), hbox_frame1);
			#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_frame2), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_frame2), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_size_request (hbox_frame2, -1, 50);
				gtk_widget_set_margin_start (hbox_frame2, 10);
				gtk_widget_set_margin_end (hbox_frame2, 10);
				gtk_widget_set_margin_top (hbox_frame2, 10);
				gtk_widget_set_margin_bottom (hbox_frame2, 10);
			#else
				gtk_widget_set_size_request (hbox_frame2, -1, 70);
				gtk_container_set_border_width (GTK_CONTAINER (hbox_frame2), 10);
			#endif
			#if GTK_CHECK_VERSION (4,0,0)
				gtk_paned_set_end_child (GTK_PANED (hpane1), hbox_frame2);
			#else
				gtk_paned_add2 (GTK_PANED (hpane1), hbox_frame2);
			#endif

			create_frames (hbox_frame1, hbox_frame2);

		#if GTK_CHECK_VERSION (4,0,0)
			gtk_paned_set_end_child (GTK_PANED (vpane), hpane2);
			gtk_paned_set_shrink_end_child (GTK_PANED (vpane), FALSE);
		#else
			gtk_paned_pack2 (GTK_PANED (vpane), hpane2, TRUE, FALSE);
		#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_notebook1), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_notebook1), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_margin_start (hbox_notebook1, 10);
				gtk_widget_set_margin_end (hbox_notebook1, 10);
				gtk_widget_set_margin_top (hbox_notebook1, 10);
				gtk_widget_set_margin_bottom (hbox_notebook1, 10);
			#else
				gtk_container_set_border_width (GTK_CONTAINER (hbox_notebook1), 10);
			#endif
			#if GTK_CHECK_VERSION (4,0,0)
				gtk_paned_set_start_child (GTK_PANED (hpane2), hbox_notebook1);
				gtk_paned_set_resize_start_child (GTK_PANED (hpane2), FALSE);
				gtk_paned_set_shrink_start_child (GTK_PANED (hpane2), FALSE);
			#else
				gtk_paned_add1 (GTK_PANED (hpane2), hbox_notebook1);
			#endif

			gtk_box_set_homogeneous (GTK_BOX (hbox_notebook2), TRUE);
			gtk_box_set_spacing (GTK_BOX (hbox_notebook2), 3);
			#if GTK_CHECK_VERSION (3,12,0)
				gtk_widget_set_margin_start (hbox_notebook2, 10);
				gtk_widget_set_margin_end (hbox_notebook2, 10);
				gtk_widget_set_margin_top (hbox_notebook2, 10);
				gtk_widget_set_margin_bottom (hbox_notebook2, 10);
			#else
				gtk_container_set_border_width (GTK_CONTAINER (hbox_notebook2), 10);
			#endif
			#if GTK_CHECK_VERSION (4,0,0)
				gtk_paned_set_end_child (GTK_PANED (hpane2), hbox_notebook2);
			#else
				gtk_paned_add2 (GTK_PANED (hpane2), hbox_notebook2);
			#endif

			create_notebooks (hbox_notebook1, hbox_notebook2);
}

static void add_to (GtkBox *box, GtkWidget *widget, gboolean fill, gboolean expand, guint padding, guint spacing) {

	#if GTK_CHECK_VERSION (4,0,0)

		if (fill && expand) {
			gtk_widget_set_halign (widget, GTK_ALIGN_FILL);
			gtk_widget_set_valign (widget, GTK_ALIGN_FILL);
			gtk_widget_set_hexpand (widget, TRUE);
			gtk_widget_set_vexpand (widget, TRUE);
		}
		else if (fill) {
			gtk_widget_set_halign (widget, GTK_ALIGN_FILL);
			gtk_widget_set_valign (widget, GTK_ALIGN_START);
			gtk_widget_set_hexpand (widget, FALSE);
			gtk_widget_set_vexpand (widget, FALSE);
		}
		else {
			gtk_widget_set_hexpand (widget, FALSE);
			gtk_widget_set_vexpand (widget, FALSE);
		}
		if (GTK_IS_BOX (widget) && (padding > 0)) {
			gtk_widget_set_margin_start (widget, padding);
			gtk_widget_set_margin_end (widget, padding);
			gtk_widget_set_margin_top (widget, padding);
			gtk_widget_set_margin_bottom (widget, padding);
		}
		if (GTK_IS_BOX (widget) && (spacing > 0)) {
			gtk_box_set_spacing (GTK_BOX (widget), spacing);
		}
		gtk_box_append (box, widget);
	#else
		if (GTK_IS_INFO_BAR (box))
			box = GTK_BOX (gtk_info_bar_get_content_area (GTK_INFO_BAR (box)));
		if (GTK_IS_CONTAINER (widget) && (padding > 0))
			gtk_container_set_border_width (GTK_CONTAINER (widget), padding);
		if (GTK_IS_BOX (widget) && (spacing > 0))
			gtk_box_set_spacing (GTK_BOX (widget), spacing);
		gtk_box_pack_start (box, widget, fill, expand, 0);
	#endif

	#if GTK_CHECK_VERSION (3,20,0)
		if (!GTK_IS_BOX (widget)) {
			GtkStyleContext *style = gtk_widget_get_style_context (widget);
			gchar *text = gtk_style_context_to_string (style, GTK_STYLE_CONTEXT_PRINT_RECURSE);
			gtk_widget_set_tooltip_text (widget, text);
			g_free (text);
		}
	#endif
}

static void create_toolbar (GtkWidget *root) {

	#if GTK_CHECK_VERSION (4,0,0)

		GtkWidget *icon1, *icon2, *icon3, *icon4, *icon5, *icon6, *icon7;

		icon1 = gtk_button_new_from_icon_name ("gtk-open");
		gtk_widget_add_css_class (icon1, "flat");
		g_signal_connect (icon1, "clicked", G_CALLBACK (dialog_open), NULL);

		icon2 = gtk_button_new_from_icon_name ("gtk-open");
		gtk_widget_set_sensitive (icon2, FALSE);

		icon3 = gtk_button_new_from_icon_name ("gtk-save");
		g_signal_connect (icon3, "clicked", G_CALLBACK (dialog_save), NULL);

		icon4 = gtk_button_new_from_icon_name ("gtk-refresh");
		g_signal_connect_swapped (icon4, "clicked", G_CALLBACK (update_theme), "refresh");

		icon5 = gtk_toggle_button_new ();
		gtk_button_set_icon_name (GTK_BUTTON (icon5), "gtk-add");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (icon5), TRUE);
		g_signal_connect (icon5, "clicked", G_CALLBACK (update_widgets), NULL);

		icon6 = gtk_toggle_button_new ();
		gtk_button_set_icon_name (GTK_BUTTON (icon6), "gtk-remove");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (icon6), FALSE);
		g_signal_connect (icon6, "clicked", G_CALLBACK (update_widgets), NULL);

		icon7 = gtk_toggle_button_new ();
		gtk_button_set_icon_name (GTK_BUTTON (icon7), "gtk-close");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (icon7), FALSE);
		gtk_widget_set_sensitive (icon7, FALSE);

		add_to (GTK_BOX (root), icon1, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), icon2, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), SEPV, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), icon3, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), icon4, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), SEPV, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), icon5, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), icon6, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root), icon7, FALSE, FALSE, 0, 0);
	#else
		GtkWidget *icon1, *icon2, *icon3, *icon4, *icon5, *icon6, *icon7, *menu;

		icon1 = GTK_WIDGET (gtk_menu_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon1), "gtk-open");
		g_signal_connect (icon1, "clicked", G_CALLBACK (dialog_open), NULL);
		menu = gtk_menu_new ();
		create_menuitem (menu, "Menu item", FALSE, NULL, NULL, NULL);
		gtk_widget_show_all (menu); // very important
		gtk_menu_tool_button_set_menu (GTK_MENU_TOOL_BUTTON (icon1), menu);

		icon2 = GTK_WIDGET (gtk_menu_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon2), "gtk-open");
		gtk_widget_set_sensitive (icon2, FALSE);

		icon3 = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon3), "gtk-save");
		g_signal_connect (icon3, "clicked", G_CALLBACK (dialog_save), NULL);

		icon4 = GTK_WIDGET (gtk_tool_button_new (NULL, NULL));
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon4), "gtk-refresh");
		g_signal_connect_swapped (icon4, "clicked", G_CALLBACK (update_theme), "refresh");

		icon5 = GTK_WIDGET (gtk_toggle_tool_button_new ());
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon5), "gtk-add");
		gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (icon5), TRUE);
		g_signal_connect (icon5, "clicked", G_CALLBACK (update_widgets), NULL);

		icon6 = GTK_WIDGET (gtk_toggle_tool_button_new ());
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon6), "gtk-remove");
		gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (icon6), FALSE);
		g_signal_connect (icon6, "clicked", G_CALLBACK (update_widgets), NULL);

		icon7 = GTK_WIDGET (gtk_toggle_tool_button_new ());
		gtk_tool_button_set_icon_name (GTK_TOOL_BUTTON (icon7), "gtk-close");
		gtk_toggle_tool_button_set_active (GTK_TOGGLE_TOOL_BUTTON (icon7), FALSE);
		gtk_widget_set_sensitive (icon7, FALSE);

		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon1), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon2), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), gtk_separator_tool_item_new (), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon3), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon4), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), gtk_separator_tool_item_new (), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon5), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon6), -1);
		gtk_toolbar_insert (GTK_TOOLBAR (root), GTK_TOOL_ITEM (icon7), -1);
	#endif
}

static void create_combos_entries (GtkWidget *root) {

	GtkWidget *combo1, *combo2, *combo3, *combo4, *entry1, *entry2, *entry3, *entry4;

	combo1 = gtk_combo_box_text_new_with_entry ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo1), "Combo box entry 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo1), "Combo box entry 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo1), 0);

	combo2 = gtk_combo_box_text_new_with_entry ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo2), "Combo box entry 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo2), "Combo box entry 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo2), 0);
	gtk_widget_set_sensitive (combo2, FALSE);

	combo3 = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo3), "Combo box 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo3), "Combo box 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo3), 0);

	combo4 = gtk_combo_box_text_new ();
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo4), "Combo box 1");
	gtk_combo_box_text_append_text (GTK_COMBO_BOX_TEXT (combo4), "Combo box 2");
	gtk_combo_box_set_active (GTK_COMBO_BOX (combo4), 0);
	gtk_widget_set_sensitive (combo4, FALSE);

	entry1 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (4,0,0)
		gtk_entry_set_placeholder_text (GTK_ENTRY (entry1), "Placeholder");
		gtk_editable_set_text (GTK_EDITABLE (entry1), "Entry");
	#elif GTK_CHECK_VERSION (3,2,0)
		gtk_entry_set_text (GTK_ENTRY (entry1), "Entry");
		gtk_entry_set_placeholder_text (GTK_ENTRY (entry1), "Placeholder");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry1), "Entry");
	#endif

	entry2 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (4,0,0)
		gtk_editable_set_text (GTK_EDITABLE (entry2), "Entry");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry2), "Entry");
	#endif
	gtk_widget_set_sensitive (entry2, FALSE);

	entry3 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (4,0,0)
		gtk_entry_set_placeholder_text (GTK_ENTRY (entry3), "Placeholder");
		gtk_editable_set_text (GTK_EDITABLE (entry3), "Entry");
	#elif GTK_CHECK_VERSION (3,2,0)
		gtk_entry_set_text (GTK_ENTRY (entry3), "Entry");
		gtk_entry_set_placeholder_text (GTK_ENTRY (entry3), "Placeholder");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry3), "Entry");
	#endif
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry3), GTK_ENTRY_ICON_PRIMARY, "gtk-clear");
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry3), GTK_ENTRY_ICON_SECONDARY, "gtk-find");

	entry4 = gtk_entry_new ();
	#if GTK_CHECK_VERSION (4,0,0)
		gtk_editable_set_text (GTK_EDITABLE (entry4), "Entry");
	#else
		gtk_entry_set_text (GTK_ENTRY (entry4), "Entry");
	#endif
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry4), GTK_ENTRY_ICON_PRIMARY, "gtk-clear");
	gtk_entry_set_icon_from_icon_name (GTK_ENTRY (entry4), GTK_ENTRY_ICON_SECONDARY, "gtk-find");
	gtk_widget_set_sensitive (entry4, FALSE);

	// layout

	add_to (GTK_BOX (root), combo1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), combo2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), combo3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), combo4, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), entry1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), entry2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), entry3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), entry4, FALSE, FALSE, 0, 0);
}

static void create_spinbuttons (GtkWidget *root) {

	GtkWidget *spinbutton1, *spinbutton2;

	spinbutton1 = gtk_spin_button_new_with_range (-100, 100, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbutton1), 1);

	spinbutton2 = gtk_spin_button_new_with_range (-100, 100, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbutton2), 1);
	gtk_widget_set_sensitive (spinbutton2, FALSE);

	add_to (GTK_BOX (root), spinbutton1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
	add_to (GTK_BOX (root), spinbutton2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
}

static void create_checkbuttons (GtkWidget *root) {

	GtkWidget *checkbutton1, *checkbutton2, *checkbutton3, *checkbutton4, *checkbutton5, *checkbutton6;

	#if GTK_CHECK_VERSION (4,0,0)

		checkbutton1 = gtk_check_button_new_with_label ("Check btn 1");

		checkbutton2 = gtk_check_button_new_with_label ("Check btn 2");
		gtk_check_button_set_active (GTK_CHECK_BUTTON (checkbutton2), TRUE);

		checkbutton3 = gtk_check_button_new_with_label ("Check btn 3");
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (checkbutton3), TRUE);

		checkbutton4 = gtk_check_button_new_with_label ("Check btn 4");
		gtk_widget_set_sensitive (checkbutton4, FALSE);

		checkbutton5 = gtk_check_button_new_with_label ("Check btn 5");
		gtk_check_button_set_active (GTK_CHECK_BUTTON (checkbutton5), TRUE);
		gtk_widget_set_sensitive (checkbutton5, FALSE);

		checkbutton6 = gtk_check_button_new_with_label ("Check btn 6");
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (checkbutton6), TRUE);
		gtk_widget_set_sensitive (checkbutton6, FALSE);
	#else
		checkbutton1 = gtk_check_button_new_with_label ("Check btn 1");

		checkbutton2 = gtk_check_button_new_with_label ("Check btn 2");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton2), TRUE);

		checkbutton3 = gtk_check_button_new_with_label ("Check btn 3");
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (checkbutton3), TRUE);

		checkbutton4 = gtk_check_button_new_with_label ("Check btn 4");
		gtk_widget_set_sensitive (checkbutton4, FALSE);

		checkbutton5 = gtk_check_button_new_with_label ("Check btn 5");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (checkbutton5), TRUE);
		gtk_widget_set_sensitive (checkbutton5, FALSE);

		checkbutton6 = gtk_check_button_new_with_label ("Check btn 6");
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (checkbutton6), TRUE);
		gtk_widget_set_sensitive (checkbutton6, FALSE);
	#endif

	add_to (GTK_BOX (root), checkbutton1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), checkbutton2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), checkbutton3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), checkbutton4, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), checkbutton5, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), checkbutton6, FALSE, FALSE, 0, 0);
}

static void create_radiobuttons (GtkWidget *root) {

	GtkWidget *radiobutton1, *radiobutton2, *radiobutton3, *radiobutton4, *radiobutton5, *radiobutton6;

	#if GTK_CHECK_VERSION (4,0,0)

		radiobutton1 = gtk_check_button_new_with_label ("Radio btn 1");
		gtk_check_button_set_group (GTK_CHECK_BUTTON (radiobutton1), NULL);

		radiobutton2 = gtk_check_button_new_with_label ("Radio btn 2");
		gtk_check_button_set_group (GTK_CHECK_BUTTON (radiobutton2), GTK_CHECK_BUTTON (radiobutton1));
		gtk_check_button_set_active (GTK_CHECK_BUTTON (radiobutton2), TRUE);

		radiobutton3 = gtk_check_button_new_with_label ("Radio btn 3");
		gtk_check_button_set_group (GTK_CHECK_BUTTON (radiobutton3), GTK_CHECK_BUTTON (radiobutton1));
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (radiobutton3), TRUE);

		radiobutton4 = gtk_check_button_new_with_label ("Radio btn 4");
		gtk_check_button_set_group (GTK_CHECK_BUTTON (radiobutton4), NULL);
		gtk_widget_set_sensitive (radiobutton4, FALSE);

		radiobutton5 = gtk_check_button_new_with_label ("Radio btn 5");
		gtk_check_button_set_group (GTK_CHECK_BUTTON (radiobutton5), GTK_CHECK_BUTTON (radiobutton4));
		gtk_check_button_set_active (GTK_CHECK_BUTTON (radiobutton5), TRUE);
		gtk_widget_set_sensitive (radiobutton5, FALSE);

		radiobutton6 = gtk_check_button_new_with_label ("Radio btn 6");
		gtk_check_button_set_group (GTK_CHECK_BUTTON (radiobutton6), GTK_CHECK_BUTTON (radiobutton4));
		gtk_check_button_set_inconsistent (GTK_CHECK_BUTTON (radiobutton6), TRUE);
		gtk_widget_set_sensitive (radiobutton6, FALSE);
	#else
		radiobutton1 = gtk_radio_button_new_with_label (NULL, "Radio btn 1");

		radiobutton2 = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton1)), "Radio btn 2");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton2), TRUE);

		radiobutton3 = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton1)), "Radio btn 3");
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (radiobutton3), TRUE);

		radiobutton4 = gtk_radio_button_new_with_label (NULL, "Radio btn 4");
		gtk_widget_set_sensitive (radiobutton4, FALSE);

		radiobutton5 = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton4)), "Radio btn 5");
		gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (radiobutton5), TRUE);
		gtk_widget_set_sensitive (radiobutton5, FALSE);

		radiobutton6 = gtk_radio_button_new_with_label (gtk_radio_button_get_group (GTK_RADIO_BUTTON (radiobutton4)), "Radio btn 6");
		gtk_toggle_button_set_inconsistent (GTK_TOGGLE_BUTTON (radiobutton6), TRUE);
		gtk_widget_set_sensitive (radiobutton6, FALSE);
	#endif

	add_to (GTK_BOX (root), radiobutton1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), radiobutton2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), radiobutton3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), radiobutton4, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), radiobutton5, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), radiobutton6, FALSE, FALSE, 0, 0);
}

static void create_otherbuttons (GtkWidget *root1, GtkWidget *root2, GtkWidget *root3, GtkWidget *root4, GtkWidget *root5) {

	GtkWidget *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9;
	GtkWidget *button10, *button11, *button12, *button13, *button14;

	button1 = gtk_button_new_with_label ("Button 1");

	button2 = gtk_button_new_with_label ("Button 2");
	gtk_widget_set_sensitive (button2, FALSE);

	button3 = gtk_toggle_button_new_with_label ("Button 3");

	button4 = gtk_toggle_button_new_with_label ("Button 4");
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (button3), TRUE);
	gtk_widget_set_sensitive (button4, FALSE);

	#if GTK_CHECK_VERSION (3,0,0)
		GdkRGBA color;
		gdk_rgba_parse (&color, "#7796ba");
		button5 = gtk_color_button_new_with_rgba (&color);
	#else
		GdkColor color;
		gdk_color_parse ("#7796ba", &color);
		button5 = gtk_color_button_new_with_color (&color);
	#endif

	button6 = gtk_font_button_new ();
	gtk_widget_set_size_request (button6, 186, -1);
	#if GTK_CHECK_VERSION (4,0,0)
		// set fixed width for font button
		gtk_label_set_ellipsize (GTK_LABEL (gtk_widget_get_first_child (gtk_widget_get_first_child (gtk_widget_get_first_child (button6)))), PANGO_ELLIPSIZE_END);
	#elif GTK_CHECK_VERSION (3,0,0)
		// set fixed width for font button
		gtk_label_set_ellipsize (GTK_LABEL (g_list_first (gtk_container_get_children (GTK_CONTAINER (gtk_bin_get_child (GTK_BIN (button6)))))->data), PANGO_ELLIPSIZE_END);
	#endif

	#if GTK_CHECK_VERSION (4,0,0)
		button7 = gtk_button_new_with_label ("Button 7");
		button8 = gtk_button_new_with_label ("Button 8");
	#else
		button7 = gtk_file_chooser_button_new ("GtkFileChooserDialog", GTK_FILE_CHOOSER_ACTION_OPEN);
		button8 = gtk_file_chooser_button_new ("GtkFileChooserDialog", GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		button9 = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (button9), TRUE);

		button10 = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (button10), TRUE);
		gtk_widget_set_sensitive (button10, FALSE);

		button11 = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (button11), FALSE);

		button12 = gtk_switch_new ();
		gtk_switch_set_active (GTK_SWITCH (button12), FALSE);
		gtk_widget_set_sensitive (button12, FALSE);
	#else
		GtkWidget *combomenu1, *combomenu2, *combomenu3, *combomenu4;

		combomenu1 = gtk_menu_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu1), gtk_menu_item_new_with_label ("Option 1"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu1), gtk_menu_item_new_with_label ("Option 2"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu1), gtk_menu_item_new_with_label ("Option 3"));

		combomenu2 = gtk_menu_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu2), gtk_menu_item_new_with_label ("Option 1"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu2), gtk_menu_item_new_with_label ("Option 2"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu2), gtk_menu_item_new_with_label ("Option 3"));

		combomenu3 = gtk_menu_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu3), gtk_menu_item_new_with_label ("Option 1"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu3), gtk_menu_item_new_with_label ("Option 2"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu3), gtk_menu_item_new_with_label ("Option 3"));

		combomenu4 = gtk_menu_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu4), gtk_menu_item_new_with_label ("Option 1"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu4), gtk_menu_item_new_with_label ("Option 2"));
		gtk_menu_shell_append (GTK_MENU_SHELL (combomenu4), gtk_menu_item_new_with_label ("Option 3"));

		button9 = gtk_option_menu_new ();
		gtk_option_menu_set_menu (GTK_OPTION_MENU (button9), combomenu1);

		button10 = gtk_option_menu_new ();
		gtk_option_menu_set_menu (GTK_OPTION_MENU (button10), combomenu2);
		gtk_widget_set_sensitive (button10, FALSE);

		button11 = gtk_option_menu_new ();
		gtk_option_menu_set_menu (GTK_OPTION_MENU (button11), combomenu3);

		button12 = gtk_option_menu_new ();
		gtk_option_menu_set_menu (GTK_OPTION_MENU (button12), combomenu4);
		gtk_widget_set_sensitive (button12, FALSE);
	#endif

	button13 = gtk_link_button_new_with_label ("https://github.com/luigifab/awf-extended", "Link button");

	button14 = gtk_link_button_new_with_label ("https://github.com/luigifab/awf-extended", "Link button");
	gtk_widget_set_sensitive (button14, FALSE);

	volume1 = gtk_volume_button_new ();
	gtk_scale_button_set_value (GTK_SCALE_BUTTON (volume1), 0.5);
	#if !GTK_CHECK_VERSION (3,12,0)
		g_object_set ((GObject*) volume1, "size", GTK_ICON_SIZE_BUTTON, NULL); // @todo not working with Ubuntu
	#endif

	volume2 = gtk_volume_button_new ();
	gtk_scale_button_set_value (GTK_SCALE_BUTTON (volume2), 0);
	gtk_widget_set_sensitive (volume2, FALSE);
	#if !GTK_CHECK_VERSION (3,12,0)
		g_object_set ((GObject*) volume2, "size", GTK_ICON_SIZE_BUTTON, NULL); // @todo not working with Ubuntu
	#endif

	// layout

	add_to (GTK_BOX (root1), button1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button4, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button5, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button6, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button7, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), button8, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root2), button9, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root2), button10, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root3), button11, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root3), button12, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root4), button13, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root4), button14, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root5), volume1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root5), volume2, FALSE, FALSE, 0, 0);
}

static void create_progressbars (GtkWidget *root1, GtkWidget *root2, GtkWidget *root3, GtkWidget *root4) {

	// progress bars

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar1 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar1), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar1), GTK_ORIENTATION_HORIZONTAL);
	#else
		progressbar1 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar1), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar1), GTK_PROGRESS_LEFT_TO_RIGHT);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar2 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar2), 0.5);
		gtk_progress_bar_set_inverted (GTK_PROGRESS_BAR (progressbar2), TRUE);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar2), GTK_ORIENTATION_HORIZONTAL);
	#else
		progressbar2 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar2), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar2), GTK_PROGRESS_RIGHT_TO_LEFT);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar3 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar3), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar3), GTK_ORIENTATION_VERTICAL);
		gtk_widget_set_size_request (progressbar3, -1, 100);
	#else
		progressbar3 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar3), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar3), GTK_PROGRESS_TOP_TO_BOTTOM);
		gtk_widget_set_size_request (progressbar3, -1, 100);
	#endif

	#if GTK_CHECK_VERSION (3,0,0)
		progressbar4 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar4), 0.5);
		gtk_progress_bar_set_inverted (GTK_PROGRESS_BAR (progressbar4), TRUE);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (progressbar4), GTK_ORIENTATION_VERTICAL);
	#else
		progressbar4 = gtk_progress_bar_new ();
		gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR (progressbar4), 0.5);
		gtk_progress_bar_set_orientation (GTK_PROGRESS_BAR (progressbar4), GTK_PROGRESS_BOTTOM_TO_TOP);
	#endif

	// scales

	scale1 = create_horizontal_scale (50, FALSE, FALSE, GTK_POS_TOP);
	g_signal_connect (scale1, "value_changed", G_CALLBACK (update_values), NULL);

	scale2 = create_horizontal_scale (50, FALSE, TRUE, GTK_POS_TOP);
	g_signal_connect (scale2, "value_changed", G_CALLBACK (update_values), NULL);

	scale3 = create_vertical_scale (50, FALSE, FALSE, GTK_POS_TOP);
	g_signal_connect (scale3, "value_changed", G_CALLBACK (update_values), NULL);

	scale4 = create_vertical_scale (50, FALSE, TRUE, GTK_POS_TOP);
	g_signal_connect (scale4, "value_changed", G_CALLBACK (update_values), NULL);

	scale5 = create_vertical_scale (50, FALSE, FALSE, GTK_POS_TOP);
	update_marks (GTK_SCALE (scale5), FALSE, GTK_POS_LEFT);
	g_signal_connect (scale5, "value_changed", G_CALLBACK (update_values), NULL);

	scale6 = create_vertical_scale (50, FALSE, TRUE, GTK_POS_TOP);
	update_marks (GTK_SCALE (scale6), FALSE, GTK_POS_RIGHT);
	g_signal_connect (scale6, "value_changed", G_CALLBACK (update_values), NULL);

	#if GTK_CHECK_VERSION (3,6,0)
		levelbar1 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar1), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar1), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar1), GTK_ORIENTATION_VERTICAL);

		levelbar2 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar2), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar2), 0.5);
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar2), GTK_ORIENTATION_VERTICAL);

		levelbar3 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar3), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar3), 2); // GTK 3.20.9 not work
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar3), GTK_ORIENTATION_VERTICAL);

		levelbar4 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar4), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar4), 2); // GTK 3.20.9 not work
		gtk_orientable_set_orientation (GTK_ORIENTABLE (levelbar4), GTK_ORIENTATION_VERTICAL);

		levelbar5 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar5), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar5), 0.5);

		levelbar6 = gtk_level_bar_new ();
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar6), GTK_LEVEL_BAR_MODE_CONTINUOUS);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar6), 0.5);

		levelbar7 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar7), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar7), 2); // GTK 3.20.9 not work

		levelbar8 = gtk_level_bar_new_for_interval (0, 5);
		gtk_level_bar_set_mode (GTK_LEVEL_BAR (levelbar8), GTK_LEVEL_BAR_MODE_DISCRETE);
		gtk_level_bar_set_value (GTK_LEVEL_BAR (levelbar8), 2); // GTK 3.20.9 not work

		#if GTK_CHECK_VERSION (3,8,0)
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar2), TRUE);
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar4), TRUE);
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar6), TRUE);
			gtk_level_bar_set_inverted (GTK_LEVEL_BAR (levelbar8), TRUE);
		#endif
	#endif

	// layout

	add_to (GTK_BOX (root1), progressbar1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), progressbar2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), scale1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root1), scale2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root2), progressbar3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root2), progressbar4, FALSE, FALSE, 0, 0);
	#if GTK_CHECK_VERSION (3,6,0)
		add_to (GTK_BOX (root2), levelbar1, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root2), levelbar2, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root2), levelbar3, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root2), levelbar4, FALSE, FALSE, 0, 0);
	#endif
	add_to (GTK_BOX (root3), scale3, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root3), scale5, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root3), scale6, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root3), scale4, FALSE, FALSE, 0, 0);
	#if GTK_CHECK_VERSION (3,6,0)
		add_to (GTK_BOX (root4), levelbar5, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root4), levelbar6, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root4), levelbar7, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (root4), levelbar8, FALSE, FALSE, 0, 0);
	#endif
}

static void create_labels (GtkWidget *root) {

	GtkWidget *label1, *label2;

	label1 = gtk_label_new ("Label 1");

	label2 = gtk_label_new ("Label 2");
	gtk_widget_set_sensitive (label2, FALSE);

	add_to (GTK_BOX (root), label1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
	add_to (GTK_BOX (root), label2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
}

static void create_spinners (GtkWidget *root) {

	GtkWidget *spinner1, *spinner2;

	spinner1 = gtk_spinner_new ();
	gtk_widget_set_size_request (spinner1, 20, 20);
	if (opt_startspinner)
		gtk_spinner_start (GTK_SPINNER (spinner1));

	spinner2 = gtk_spinner_new ();
	gtk_widget_set_size_request (spinner2, 20, 20);
	gtk_widget_set_sensitive (spinner2, FALSE);
	if (opt_startspinner)
		gtk_spinner_start (GTK_SPINNER (spinner2));

	add_to (GTK_BOX (root), spinner1, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
	add_to (GTK_BOX (root), spinner2, FALSE, FALSE, 0, 0);
	add_to (GTK_BOX (root), BOXH, TRUE, TRUE, 0, 0); // empty space
}

static void create_expander (GtkWidget *root) {

	GtkWidget *expander, *scrolled_window, *tv;
	GtkTextBuffer *buffer;

	expander = gtk_expander_new (_app("More..."));
	gtk_expander_set_expanded (GTK_EXPANDER (expander), TRUE);
	//#if GTK_CHECK_VERSION (3,20,0) && !GTK_CHECK_VERSION (4,0,0)
	//	how to set label width to 100% ?
	//#endif

	#if GTK_CHECK_VERSION (4,0,0)
		scrolled_window = gtk_scrolled_window_new ();
		const gchar *config = g_getenv ("GTK_OVERLAY_SCROLLING");
		if (config && (strcmp (config, "0") == 0))
			gtk_scrolled_window_set_overlay_scrolling (GTK_SCROLLED_WINDOW (scrolled_window), FALSE);
	#else
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window), GTK_SHADOW_IN);
	#endif

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
	gtk_widget_set_size_request (scrolled_window, -1, 120);

	tv = gtk_text_view_new ();
	buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (tv), GTK_WRAP_WORD);
	gtk_text_buffer_set_text (GTK_TEXT_BUFFER (buffer), g_strdup_printf ("%s ~ %s", _app("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme."), _app("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme.")), -1);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled_window), tv);
		gtk_expander_set_child (GTK_EXPANDER (expander), scrolled_window);
	#else
		gtk_container_add (GTK_CONTAINER (scrolled_window), tv);
		gtk_container_add (GTK_CONTAINER (expander), scrolled_window);
	#endif

	add_to (GTK_BOX (root), expander, FALSE, FALSE, 0, 0);
}

static void create_frames (GtkWidget *root1, GtkWidget *root2) {

	GtkWidget *frame1, *frame2, *frame3, *frame4;

	#if GTK_CHECK_VERSION (4,0,0)
		frame1 = gtk_frame_new ("Frame (shadow in)");
		gtk_widget_add_css_class (frame1, "border-inset");

		frame2 = gtk_frame_new ("Frame (shadow out)");
		gtk_widget_add_css_class (frame2, "border-outset");

		frame3 = gtk_frame_new ("Frame (shadow etched in)");
		gtk_widget_add_css_class (frame3, "border-groove");

		frame4 = gtk_frame_new ("Frame (shadow etched out)");
		gtk_widget_add_css_class (frame4, "border-ridge");
	#elif GTK_CHECK_VERSION (3,0,0)
		frame1 = gtk_frame_new ("Frame (shadow in)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame1), "border-inset");
		gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_IN);

		frame2 = gtk_frame_new ("Frame (shadow out)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame2), "border-outset");
		gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_OUT);

		frame3 = gtk_frame_new ("Frame (shadow etched in)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame3), "border-groove");
		gtk_frame_set_shadow_type (GTK_FRAME (frame3), GTK_SHADOW_ETCHED_IN);

		frame4 = gtk_frame_new ("Frame (shadow etched out)");
		gtk_style_context_add_class (gtk_widget_get_style_context (frame4), "border-ridge");
		gtk_frame_set_shadow_type (GTK_FRAME (frame4), GTK_SHADOW_ETCHED_OUT);
	#else
		frame1 = gtk_frame_new ("Frame (shadow in)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_IN);

		frame2 = gtk_frame_new ("Frame (shadow out)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame2), GTK_SHADOW_OUT);

		frame3 = gtk_frame_new ("Frame (shadow etched in)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame3), GTK_SHADOW_ETCHED_IN);

		frame4 = gtk_frame_new ("Frame (shadow etched out)");
		gtk_frame_set_shadow_type (GTK_FRAME (frame4), GTK_SHADOW_ETCHED_OUT);
	#endif

	add_to (GTK_BOX (root1), frame1, TRUE, TRUE, 0, 0);
	add_to (GTK_BOX (root1), frame2, TRUE, TRUE, 0, 0);
	add_to (GTK_BOX (root2), frame3, TRUE, TRUE, 0, 0);
	add_to (GTK_BOX (root2), frame4, TRUE, TRUE, 0, 0);
}

static void create_notebooks (GtkWidget *root1, GtkWidget *root2) {

	notebook1 = gtk_notebook_new ();
	notebook2 = gtk_notebook_new ();
	notebook3 = gtk_notebook_new ();
	notebook4 = gtk_notebook_new ();

	#if GTK_CHECK_VERSION (3,4,0) && !GTK_CHECK_VERSION (4,0,0)
		// gtk-scroll-tabs for GTK 3.4 to 3.24
		// with or without gtk3-classic https://github.com/lah7/gtk3-classic/commit/66b65775822c46e07f5b2f30036010d06dbcbad4
		gtk_widget_add_events (notebook1, GDK_SCROLL_MASK);
		g_signal_connect (notebook1, "scroll-event", G_CALLBACK (on_scrolltabs), NULL);
		gtk_widget_add_events (notebook2, GDK_SCROLL_MASK);
		g_signal_connect (notebook2, "scroll-event", G_CALLBACK (on_scrolltabs), NULL);
		gtk_widget_add_events (notebook3, GDK_SCROLL_MASK);
		g_signal_connect (notebook3, "scroll-event", G_CALLBACK (on_scrolltabs), NULL);
		gtk_widget_add_events (notebook4, GDK_SCROLL_MASK);
		g_signal_connect (notebook4, "scroll-event", G_CALLBACK (on_scrolltabs), NULL);
	#endif

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook1));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook1), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook1), GTK_POS_TOP);
		create_notebook_tab (notebook1, "Tab1", FALSE);
		create_notebook_tab (notebook1, "Tab2", FALSE);
		create_notebook_tab (notebook1, "Tab3", TRUE);
		create_notebook_tab (notebook1, "Tab4", TRUE);

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook2));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook2), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook2), GTK_POS_BOTTOM);
		create_notebook_tab (notebook2, "Tab1", FALSE);
		create_notebook_tab (notebook2, "Tab2", FALSE);
		create_notebook_tab (notebook2, "Tab3", TRUE);
		create_notebook_tab (notebook2, "Tab4", TRUE);

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook3));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook3), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook3), GTK_POS_LEFT);
		create_notebook_tab (notebook3, "T1", FALSE);
		create_notebook_tab (notebook3, "Tab2", FALSE);
		create_notebook_tab (notebook3, "T3b", TRUE);
		create_notebook_tab (notebook3, "T4", TRUE);

	gtk_notebook_popup_enable (GTK_NOTEBOOK (notebook4));
	gtk_notebook_set_scrollable (GTK_NOTEBOOK (notebook4), FALSE);
	gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook4), GTK_POS_RIGHT);
		create_notebook_tab (notebook4, "T1", FALSE);
		create_notebook_tab (notebook4, "Tab2", FALSE);
		create_notebook_tab (notebook4, "T3b", TRUE);
		create_notebook_tab (notebook4, "T4", TRUE);

	add_to (GTK_BOX (root1), notebook1, TRUE, TRUE, 0, 0);
	add_to (GTK_BOX (root1), notebook2, TRUE, TRUE, 0, 0);
	add_to (GTK_BOX (root2), notebook3, TRUE, TRUE, 0, 0);
	add_to (GTK_BOX (root2), notebook4, TRUE, TRUE, 0, 0);
}

static void create_notebook_tab (GtkWidget *notebook, gchar *text, gboolean close) {

	GtkWidget *headbtn = BOXH, *content = BOXV, *btn;
	add_to (GTK_BOX (headbtn), gtk_label_new (text), TRUE, TRUE, 0, 0);

	if (close) {

		#if GTK_CHECK_VERSION (4,0,0)
			btn = gtk_button_new_from_icon_name ("gtk-close");
			gtk_button_set_has_frame (GTK_BUTTON (btn), FALSE);

			GtkCssProvider *provider = gtk_css_provider_new ();
			gtk_css_provider_load_from_data (provider, "notebook tab button { padding:0; }", -1);
			gtk_style_context_add_provider_for_display (
				gtk_widget_get_display (GTK_WIDGET (btn)),
				GTK_STYLE_PROVIDER (provider),
				GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		#elif GTK_CHECK_VERSION (3,0,0)
			btn = gtk_button_new ();
			gtk_button_set_image (GTK_BUTTON (btn), gtk_image_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_MENU));
			gtk_button_set_relief (GTK_BUTTON (btn), GTK_RELIEF_NONE);

			GtkCssProvider *provider = gtk_css_provider_new ();
			gtk_css_provider_load_from_data (provider, "* { padding:0; }", -1, NULL);
			gtk_style_context_add_provider (
				gtk_widget_get_style_context (GTK_WIDGET (btn)),
				GTK_STYLE_PROVIDER (provider),
				GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
		#else
			btn = gtk_button_new ();
			gtk_button_set_image (GTK_BUTTON (btn), gtk_image_new_from_icon_name ("gtk-close", GTK_ICON_SIZE_MENU));
			gtk_button_set_relief (GTK_BUTTON (btn), GTK_RELIEF_NONE);

			gtk_widget_set_name (btn, "close-button");
			gtk_rc_parse_string ("style \"close-button\"\n"
				"{\n"
					"GtkWidget::focus-padding = 0\n"
					"GtkWidget::focus-line-width = 0\n"
					"xthickness = 0\n"
					"ythickness = 0\n"
				"}\n"
				"widget \"*.close-button\" style \"close-button\"");
		#endif

		#if GTK_CHECK_VERSION (3,20,0)
			gtk_widget_set_focus_on_click (btn, FALSE);
		#else
			gtk_button_set_focus_on_click (GTK_BUTTON (btn), FALSE);
		#endif

		add_to (GTK_BOX (headbtn), btn, FALSE, FALSE, 0, 0);
	}

	#if !GTK_CHECK_VERSION (4,0,0)
		gtk_widget_show_all (headbtn);
	#endif

	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), content, headbtn);
	gtk_notebook_set_tab_reorderable (GTK_NOTEBOOK (notebook), content, TRUE);

	#if GTK_CHECK_VERSION (4,0,0)
		// gtk-scroll-tabs for GTK 4.x
		GtkEventController *event;
		event = gtk_event_controller_scroll_new (GTK_EVENT_CONTROLLER_SCROLL_BOTH_AXES | GTK_EVENT_CONTROLLER_SCROLL_DISCRETE);
		g_signal_connect (event, "scroll", G_CALLBACK (on_scrolltabs), notebook);
		gtk_widget_add_controller (gtk_widget_get_parent (headbtn), event);
	#elif GTK_CHECK_VERSION (3,4,0)
		if (close) {
			// gtk-scroll-tabs (close button) for GTK 3.4 to 3.24
			// with or without gtk3-classic https://github.com/lah7/gtk3-classic/commit/66b65775822c46e07f5b2f30036010d06dbcbad4
			gtk_widget_add_events (btn, GDK_SCROLL_MASK);
			g_signal_connect (btn, "scroll-event", G_CALLBACK (on_scrolltabs), NULL);
		}
	#endif
}

static void create_treview (GtkWidget *root) {

	GtkWidget *scrolled_window, *view;
	GtkCellRenderer *renderer;
	GtkTreeStore *store;
	GtkTreeIter iter;
	int idx = 0;

	#if GTK_CHECK_VERSION (4,0,0)
		G_GNUC_BEGIN_IGNORE_DEPRECATIONS
	#endif

	// data
	store = gtk_tree_store_new (11,
		G_TYPE_INT,
		G_TYPE_BOOLEAN,
		G_TYPE_BOOLEAN,
		G_TYPE_STRING,
		G_TYPE_DOUBLE,
		G_TYPE_DOUBLE,
		G_TYPE_STRING,
		G_TYPE_STRING,
		G_TYPE_STRING,
		G_TYPE_BOOLEAN,
		G_TYPE_BOOLEAN);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 1,
		1, FALSE,
		2, FALSE,
		3, "Text 1.1",
		4, 0.0,
		5, 0.0,
		6, "Text 1.2",
		7, "gtk-open",
		8, "gtk-open",
		9, FALSE,
		10, FALSE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 2,
		1, TRUE,
		2, TRUE,
		3, "Text 2.1",
		4, 10.0,
		5, 10.0,
		6, "Text 2.2",
		7, "gtk-save",
		8, "gtk-save",
		9, TRUE,
		10, TRUE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 3,
		1, FALSE,
		2, FALSE,
		3, "Text 3.1",
		4, 20.0,
		5, 20.0,
		6, "Text 3.2",
		7, "gtk-save-as",
		8, "gtk-save-as",
		9, FALSE,
		10, FALSE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 4,
		1, TRUE,
		2, TRUE,
		3, "Text 4.1",
		4, 30.0,
		5, 30.0,
		6, "Text 4.2",
		7, "gtk-refresh",
		8, "gtk-refresh",
		9, TRUE,
		10, TRUE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 5,
		1, FALSE,
		2, FALSE,
		3, "Text 5.1",
		4, 40.0,
		5, 40.0,
		6, "Text 5.2",
		7, "gtk-cut",
		8, "gtk-cut",
		9, FALSE,
		10, FALSE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 6,
		1, TRUE,
		2, TRUE,
		3, "Text 6.1",
		4, 50.0,
		5, 50.0,
		6, "Text 6.2",
		7, "gtk-help",
		8, "gtk-help",
		9, TRUE,
		10, TRUE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 7,
		1, FALSE,
		2, FALSE,
		3, "Text 7.1",
		4, 60.0,
		5, 60.0,
		6, "Text 7.2",
		7, "gtk-open",
		8, "gtk-open",
		9, FALSE,
		10, FALSE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 8,
		1, TRUE,
		2, TRUE,
		3, "Text 8.1",
		4, 70.0,
		5, 70.0,
		6, "Text 8.2",
		7, "gtk-save",
		8, "gtk-save",
		9, TRUE,
		10, TRUE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 9,
		1, FALSE,
		2, FALSE,
		3, "Text 9.1",
		4, 80.0,
		5, 80.0,
		6, "Text 9.2",
		7, "gtk-save-as",
		8, "gtk-save-as",
		9, FALSE,
		10, FALSE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 10,
		1, TRUE,
		2, TRUE,
		3, "Text 10.1",
		4, 90.0,
		5, 90.0,
		6, "Text 10.2",
		7, "gtk-refresh",
		8, "gtk-refresh",
		9, TRUE,
		10, TRUE,
		-1);
	gtk_tree_store_append (store, &iter, NULL);
	gtk_tree_store_set (store, &iter,
		0, 11,
		1, FALSE,
		2, FALSE,
		3, "Text 11.1",
		4, 100.0,
		5, 100.0,
		6, "Text 11.2",
		7, "gtk-cut",
		8, "gtk-cut",
		9, FALSE,
		10, FALSE,
		-1);

	// columns
	view = gtk_tree_view_new_with_model (GTK_TREE_MODEL (store));
	gtk_tree_view_set_reorderable (GTK_TREE_VIEW (view), FALSE); // rows
	gtk_tree_view_set_show_expanders (GTK_TREE_VIEW (view), FALSE);
	gtk_tree_view_set_headers_clickable (GTK_TREE_VIEW (view), TRUE);
	gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (store), 0, GTK_SORT_ASCENDING);
	g_object_unref (G_OBJECT (store));

	idx = 0;
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "i", renderer, "text", idx, NULL);
	gtk_tree_view_column_set_sort_column_id (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), idx);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 1;
	renderer = gtk_cell_renderer_toggle_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "c", renderer, "active", idx, NULL);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_min_width (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), 20);

	idx = 2;
	renderer = gtk_cell_renderer_toggle_new ();
	gtk_cell_renderer_toggle_set_radio (GTK_CELL_RENDERER_TOGGLE (renderer), TRUE);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "r", renderer, "active", idx, NULL);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_min_width (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), 20);

	idx = 3;
	renderer = gtk_cell_renderer_text_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "Text", renderer, "text", idx, NULL);
	gtk_tree_view_column_set_sort_column_id (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), idx);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 4;
	renderer = gtk_cell_renderer_progress_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "Progress", renderer, "value", idx, NULL);
	gtk_tree_view_column_set_sort_column_id (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), idx);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 5;
	renderer = gtk_cell_renderer_progress_new ();
	gtk_cell_renderer_set_sensitive (renderer, FALSE);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "Progress", renderer, "value", idx, NULL);
	gtk_tree_view_column_set_sort_column_id (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), idx);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 6;
	renderer = gtk_cell_renderer_text_new ();
	gtk_cell_renderer_set_sensitive (renderer, FALSE);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "Text", renderer, "text", idx, NULL);
	gtk_tree_view_column_set_sort_column_id (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), idx);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 7;
	renderer = gtk_cell_renderer_pixbuf_new ();
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "Icon", renderer, "icon-name", idx, NULL);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 8;
	renderer = gtk_cell_renderer_pixbuf_new ();
	gtk_cell_renderer_set_sensitive (renderer, FALSE);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "Icon", renderer, "icon-name", idx, NULL);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);

	idx = 9;
	renderer = gtk_cell_renderer_toggle_new ();
	gtk_cell_renderer_set_sensitive (renderer, FALSE);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "c", renderer, "active", idx, NULL);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_min_width (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), 20);

	idx = 10;
	renderer = gtk_cell_renderer_toggle_new ();
	gtk_cell_renderer_set_sensitive (renderer, FALSE);
	gtk_cell_renderer_toggle_set_radio (GTK_CELL_RENDERER_TOGGLE (renderer), TRUE);
	gtk_tree_view_insert_column_with_attributes (GTK_TREE_VIEW (view), idx, "r", renderer, "active", idx, NULL);
	gtk_tree_view_column_set_reorderable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_resizable (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), TRUE);
	gtk_tree_view_column_set_min_width (gtk_tree_view_get_column (GTK_TREE_VIEW (view), idx), 20);

	#if GTK_CHECK_VERSION (4,0,0)
		G_GNUC_END_IGNORE_DEPRECATIONS
	#endif

	// colors
	#if GTK_CHECK_VERSION (4,0,0)
		// gtk_tree_view_set_grid_lines (GTK_TREE_VIEW (view), GTK_TREE_VIEW_GRID_LINES_VERTICAL);
	#elif GTK_CHECK_VERSION (3,19,0)
		// with gtk3-classic https://github.com/lah7/gtk3-classic/blob/master/treeview__alternating_row_colours.patch
	#else
		gtk_tree_view_set_rules_hint (GTK_TREE_VIEW (view), TRUE);
	#endif

	// scrolled window
	#if GTK_CHECK_VERSION (4,0,0)
		scrolled_window = gtk_scrolled_window_new ();
		const gchar *config = g_getenv ("GTK_OVERLAY_SCROLLING");
		if (config && (strcmp (config, "0") == 0))
			gtk_scrolled_window_set_overlay_scrolling (GTK_SCROLLED_WINDOW (scrolled_window), FALSE);
	#else
		scrolled_window = gtk_scrolled_window_new (NULL, NULL);
		gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (scrolled_window), GTK_SHADOW_IN);
	#endif

	gtk_widget_set_size_request (view, 200, 200);
	gtk_widget_set_size_request (scrolled_window, 200, 200);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_window), GTK_POLICY_ALWAYS, GTK_POLICY_ALWAYS);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scrolled_window), view);
	#else
		gtk_container_add (GTK_CONTAINER (scrolled_window), view);
	#endif

	add_to (GTK_BOX (root), scrolled_window, FALSE, FALSE, 0, 0);
}

static GtkWidget* create_horizontal_scale (gdouble value, gboolean draw, gboolean inverted, int position) {

	GtkWidget *scale;

	#if GTK_CHECK_VERSION (3,0,0)
		scale = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
	#else
		scale = gtk_hscale_new_with_range (0, 100, 1);
	#endif

	gtk_range_set_value (GTK_RANGE (scale), value);
	gtk_scale_set_draw_value (GTK_SCALE (scale), draw);
	gtk_scale_set_value_pos (GTK_SCALE (scale), position);
	gtk_range_set_inverted (GTK_RANGE (scale), inverted);
	gtk_widget_set_size_request (scale, 186, -1);

	return scale;
}

static GtkWidget* create_vertical_scale (gdouble value, gboolean draw, gboolean inverted, int position) {

	GtkWidget *scale;

	#if GTK_CHECK_VERSION (3,0,0)
		scale = gtk_scale_new_with_range (GTK_ORIENTATION_VERTICAL, 0, 100, 1);
	#else
		scale = gtk_vscale_new_with_range (0, 100, 1);
	#endif

	gtk_scale_set_value_pos (GTK_SCALE (scale), position);
	gtk_range_set_inverted (GTK_RANGE (scale), inverted);
	gtk_scale_set_draw_value (GTK_SCALE (scale), draw);
	gtk_range_set_value (GTK_RANGE (scale), value);
	gtk_widget_set_size_request (scale, -1, 100);

	return scale;
}


// traditional menu (gtk4 or gtk3/gtk2)

#if GTK_CHECK_VERSION (4,0,0)

static void closedialog (GtkDialog *dialog) {
	gtk_window_destroy (GTK_WINDOW (dialog));
}

static void activate_action (GSimpleAction *action, GVariant *parameter, gpointer data) {

	GVariant *action_state;

	// radio
	if (parameter) {
		g_simple_action_set_state (action, parameter);
		if (strcmp ((gchar*) g_action_get_name (G_ACTION (action)), "set-theme") == 0)
			update_theme ((gchar*) g_variant_get_string (parameter, NULL));
		else if (strcmp ((gchar*) g_action_get_name (G_ACTION (action)), "set-direction") == 0)
			update_text_direction ((strcmp (g_variant_get_string (parameter, NULL), "1") == 0) ? 1 : 2);
	}
	// checkbox
	else {
		action_state = g_action_get_state (G_ACTION (action));
		if (g_variant_get_boolean (action_state) == FALSE)
			g_simple_action_set_state (action, g_variant_new_boolean (TRUE));
		else
			g_simple_action_set_state (action, g_variant_new_boolean (FALSE));
	}
}

static void create_traditional_menubar (GtkApplication *app, GMenu *root) {

	GMenu *menu, *submenu, *section;
	GSimpleAction *action;
	GSList *iterator;

	// options
	menu = g_menu_new ();
	g_menu_append_submenu (root, _app("_Options"), G_MENU_MODEL (menu));

		create_menuitem (app, menu, _gtk("_Open"), AWF_ACCEL_OPEN, AWF_OPEN, dialog_open);
		create_menuitem (app, menu, _app("Open recent file"), AWF_ACCEL_RECE, AWF_RECE, dialog_recent);
		create_menuitem (app, menu, _app("Calendar"), AWF_ACCEL_CALE, AWF_CALE, dialog_calendar);
		create_menuitem (app, menu, _app("GtkScales top"), AWF_ACCEL_SCAT, AWF_SCAT, dialog_scales_top);
		create_menuitem (app, menu, _app("GtkScales bottom"), AWF_ACCEL_SCAB, AWF_SCAB, dialog_scales_bottom);
		create_menuitem (app, menu, _app("GtkScales right"), AWF_ACCEL_SCAR, AWF_SCAR, dialog_scales_right);
		create_menuitem (app, menu, _app("GtkScales left"), AWF_ACCEL_SCAL, AWF_SCAL, dialog_scales_left);
		create_menuitem (app, menu, _gtk("_Save"), AWF_ACCEL_SAVE, AWF_SAVE, dialog_save);
		create_menuitem (app, menu, _gtk("_Refresh"), AWF_ACCEL_REFR, AWF_REFR, G_CALLBACK (on_sighup)); // G_CALLBACK (update_theme)
		create_menuitem (app, menu, _gtk("_Properties"), AWF_ACCEL_PROP, AWF_PROP, dialog_message);
		create_menuitem (app, menu, _gtk("Page Set_up"), AWF_ACCEL_PRSE, AWF_PRSE, dialog_page_setup);
		create_menuitem (app, menu, _gtk("_Print"), AWF_ACCEL_PRIN, AWF_PRIN, dialog_print);
		create_menuitem (app, menu, _gtk("_About"), AWF_ACCEL_ABOU, AWF_ABOU, dialog_about);

		submenu = g_menu_new ();
		g_menu_append_submenu (menu, _app("More..."), G_MENU_MODEL (submenu));

			create_menuitem (app, submenu, _gtk("Cu_t"), AWF_ACCEL_MCUT, AWF_MCUT, NULL);
			create_menuitem (app, submenu, _gtk("_Copy"), AWF_ACCEL_MCOP, AWF_MCOP, NULL);
			create_menuitem (app, submenu, _gtk("_Paste"), AWF_ACCEL_MPAS, AWF_MPAS, NULL);

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			action = g_simple_action_new_stateful ("set-check-grp11", NULL, g_variant_new_boolean (FALSE));
			g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
			g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));
			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Check 1 %s", _app("(unchecked)")), "app.set-check-grp11"));

			action = g_simple_action_new_stateful ("set-check-grp12", NULL, g_variant_new_boolean (TRUE));
			g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
			g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));
			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Check 2 %s", _app("(checked)")), "app.set-check-grp12"));

			g_menu_append_item (section, g_menu_item_new ("Empty", NULL)); // @todo

			action = g_simple_action_new_stateful ("set-check-grp21", NULL, g_variant_new_boolean (FALSE));
			g_simple_action_set_enabled (action, FALSE);
			g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
			g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));
			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Check 1 %s", _app("(unchecked)")), "app.set-check-grp21"));

			action = g_simple_action_new_stateful ("set-check-grp22", NULL, g_variant_new_boolean (TRUE));
			g_simple_action_set_enabled (action, FALSE);
			g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
			g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));
			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Check 2 %s", _app("(checked)")), "app.set-check-grp22"));

			g_menu_append_item (section, g_menu_item_new ("Empty", "disabled")); // @todo

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			action = g_simple_action_new_stateful ("set-radio-grp1", G_VARIANT_TYPE_STRING, g_variant_new_string ("checked"));
			g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
			g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));

			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Radio 1 %s", _app("(unchecked)")), "app.set-radio-grp1::unchecked"));
			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Radio 2 %s", _app("(checked)")), "app.set-radio-grp1::checked"));
			g_menu_append_item (section, g_menu_item_new ("Empty", NULL)); // @todo

			action = g_simple_action_new_stateful ("set-radio-grp2", G_VARIANT_TYPE_STRING, g_variant_new_string ("checked"));
			g_simple_action_set_enabled (action, FALSE);
			g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
			g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));

			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Radio 1 %s", _app("(unchecked)")), "app.set-radio-grp2::unchecked"));
			g_menu_append_item (section, g_menu_item_new (g_strdup_printf ("Radio 2 %s", _app("(checked)")), "app.set-radio-grp2::checked"));
			g_menu_append_item (section, g_menu_item_new ("Empty", "disabled")); // @todo

		section = g_menu_new ();
		g_menu_append_section (menu, NULL, G_MENU_MODEL (section));

			create_menuitem (app, section, _gtk("_Close"), AWF_ACCEL_CLOS, AWF_CLOS, NULL);
			create_menuitem (app, section, _gtk("_Quit"), AWF_ACCEL_QUIT, AWF_QUIT, quit);

	// themes
	action = g_simple_action_new_stateful ("set-theme", G_VARIANT_TYPE_STRING, g_variant_new_string (current_theme));
	g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
	g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));

	// system themes
	menu = g_menu_new ();
	g_menu_append_submenu (root, _app("_System themes"), G_MENU_MODEL (menu));
	for (iterator = list_system_theme; iterator; iterator = iterator->next) {
		if (g_slist_find_custom (list_user_theme, iterator->data, &awf_compare_theme))
			g_menu_append_item (menu, g_menu_item_new (iterator->data, "disabled")); // @todo
		else
			g_menu_append_item (menu, g_menu_item_new (iterator->data, g_strdup_printf ("app.set-theme::%s", (gchar*) iterator->data)));
	}

	if (!list_system_theme)
		g_menu_append (menu, _app("No themes found"), "disabled"); // @todo

	// user themes
	menu = g_menu_new ();
	g_menu_append_submenu (root, _app("_User themes"), G_MENU_MODEL (menu));
	for (iterator = list_user_theme; iterator; iterator = iterator->next)
		g_menu_append_item (menu, g_menu_item_new (iterator->data, g_strdup_printf ("app.set-theme::%s", (gchar*) iterator->data)));

	if (!list_user_theme)
		g_menu_append (menu, _app("No themes found"), "disabled"); // @todo

	// text direction
	if ((current_direction == GTK_TEXT_DIR_LTR) || (current_direction == 1))
		action = g_simple_action_new_stateful ("set-direction", G_VARIANT_TYPE_STRING, g_variant_new_string ("1"));
	if ((current_direction == GTK_TEXT_DIR_RTL) || (current_direction == 2))
		action = g_simple_action_new_stateful ("set-direction", G_VARIANT_TYPE_STRING, g_variant_new_string ("2"));
	g_signal_connect (action, "activate", G_CALLBACK (activate_action), NULL);
	g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));

	menu = g_menu_new ();
	g_menu_append_submenu (root, _app("_Text direction"), G_MENU_MODEL (menu));
		g_menu_append_item (menu, g_menu_item_new (_app("Left to Right (LTR)"), g_strdup_printf ("app.set-direction::%d", GTK_TEXT_DIR_LTR)));
		g_menu_append_item (menu, g_menu_item_new (_app("Right to Left (RTL)"), g_strdup_printf ("app.set-direction::%d", GTK_TEXT_DIR_RTL)));
}

static GMenuItem* create_menuitem (GtkApplication *app, GMenu *menu, gchar *text, gchar *accel, gchar *keymap, GCallback function) {

	GMenuItem *menuitem;
	GSimpleAction *action;
	gchar *acckey[2] = { accel, NULL };
	gchar *appkey = g_strdup_printf ("app.%s", keymap);

	action = g_simple_action_new (keymap, NULL);
	g_action_map_add_action (G_ACTION_MAP (g_application_get_default ()), G_ACTION (action));
	gtk_application_set_accels_for_action (app, appkey, (const char**) acckey);

	menuitem = g_menu_item_new (text, appkey);

	if (function)
		g_signal_connect (action, "activate", function, NULL);
	if (accel)
		g_menu_item_set_attribute (menuitem, "accel", "s", accel, NULL);

	g_menu_append_item (menu, menuitem);
	g_free (appkey);

	return menuitem;
}

static void accels_change (GtkEventControllerKey *controller, guint keyval, guint keycode, GdkModifierType state) {

	// gtk-can-change-accels for GTK 4.x
	// @todo
}

static void accels_save () {

	// gtk-can-change-accels for GTK 4.x
	// @todo
}

#else

static void create_traditional_menubar (GtkWidget *root) {

	GtkWidget *menu, *submenu, *menuitem;
	GtkAccelGroup *accels = gtk_accel_group_new ();
	GSList *iterator, *group = NULL;

	gtk_window_add_accel_group (GTK_WINDOW (window), accels);

	// options
	menu = create_menu (root, _app("_Options"));
	gtk_menu_set_accel_group (GTK_MENU (menu), accels); // very important

		create_menuitem_tearoff (menu);

		create_menuitem (menu, "gtk-open", FALSE, AWF_ACCEL_OPEN, AWF_OPEN, dialog_open);
		create_menuitem (menu, _app("Open recent file"), FALSE, AWF_ACCEL_RECE, AWF_RECE, dialog_recent);
		create_menuitem (menu, _app("Calendar"), FALSE, AWF_ACCEL_CALE, AWF_CALE, dialog_calendar);
		create_menuitem (menu, _app("GtkScales top"), FALSE, AWF_ACCEL_SCAT, AWF_SCAT, dialog_scales_top);
		create_menuitem (menu, _app("GtkScales bottom"), FALSE, AWF_ACCEL_SCAB, AWF_SCAB, dialog_scales_bottom);
		create_menuitem (menu, _app("GtkScales right"), FALSE, AWF_ACCEL_SCAR, AWF_SCAR, dialog_scales_right);
		create_menuitem (menu, _app("GtkScales left"), FALSE, AWF_ACCEL_SCAL, AWF_SCAL, dialog_scales_left);
		create_menuitem (menu, "gtk-save", FALSE, AWF_ACCEL_SAVE, AWF_SAVE, dialog_save);
		create_menuitem (menu, "gtk-refresh", FALSE, AWF_ACCEL_REFR, AWF_REFR, G_CALLBACK (on_sighup)); // G_CALLBACK (update_theme)
		create_menuitem (menu, "gtk-properties", FALSE, AWF_ACCEL_PROP, AWF_PROP, dialog_message);
		create_menuitem (menu, "gtk-page-setup", FALSE, AWF_ACCEL_PRSE, AWF_PRSE, dialog_page_setup);
		create_menuitem (menu, "gtk-print", FALSE, AWF_ACCEL_PRIN, AWF_PRIN, dialog_print);
		create_menuitem (menu, "gtk-about", FALSE, AWF_ACCEL_ABOU, AWF_ABOU, dialog_about);

		submenu = create_menu (menu, _app("More..."));
		gtk_menu_set_accel_group (GTK_MENU (submenu), accels); // very important

			create_menuitem (submenu, "gtk-cut", FALSE, AWF_ACCEL_MCUT, AWF_MCUT, NULL);
			create_menuitem (submenu, "gtk-copy", FALSE, AWF_ACCEL_MCOP, AWF_MCOP, NULL);
			create_menuitem (submenu, "gtk-paste", FALSE, AWF_ACCEL_MPAS, AWF_MPAS, NULL);

		menuitem = gtk_separator_menu_item_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

			create_menuitem_check (menu, g_strdup_printf ("Check 1 %s", _app("(unchecked)")), FALSE, FALSE, FALSE);
			create_menuitem_check (menu, g_strdup_printf ("Check 2 %s", _app("(checked)")), TRUE, FALSE, FALSE);
			create_menuitem_check (menu, g_strdup_printf ("Check 3 %s", _app("(inconsistent)")), FALSE, TRUE, FALSE);

			create_menuitem_check (menu, g_strdup_printf ("Check 1 %s", _app("(unchecked)")), FALSE, FALSE, TRUE);
			create_menuitem_check (menu, g_strdup_printf ("Check 2 %s", _app("(checked)")), TRUE, FALSE, TRUE);
			create_menuitem_check (menu, g_strdup_printf ("Check 3 %s", _app("(inconsistent)")), FALSE, TRUE, TRUE);

		menuitem = gtk_separator_menu_item_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

			menuitem = create_menuitem_radio (menu, g_strdup_printf ("Radio 1 %s", _app("(unchecked)")), FALSE, FALSE, FALSE, NULL);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
					 create_menuitem_radio (menu, g_strdup_printf ("Radio 2 %s", _app("(checked)")), TRUE, FALSE, FALSE, group);
					 create_menuitem_radio (menu, g_strdup_printf ("Radio 3 %s", _app("(inconsistent)")), FALSE, TRUE, FALSE, NULL);

			menuitem = create_menuitem_radio (menu, g_strdup_printf ("Radio 1 %s", _app("(unchecked)")), FALSE, FALSE, TRUE, NULL);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
					 create_menuitem_radio (menu, g_strdup_printf ("Radio 2 %s", _app("(checked)")), TRUE, FALSE, TRUE, group);
					 create_menuitem_radio (menu, g_strdup_printf ("Radio 3 %s", _app("(inconsistent)")), FALSE, TRUE, TRUE, NULL);

		menuitem = gtk_separator_menu_item_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

			create_menuitem (menu, "gtk-close", TRUE, AWF_ACCEL_CLOS, AWF_CLOS, NULL);
			create_menuitem (menu, "gtk-quit", FALSE, AWF_ACCEL_QUIT, AWF_QUIT, quit);

	// system themes
	group = NULL;
	menu  = create_menu (root, _app("_System themes"));
	for (iterator = list_system_theme; iterator; iterator = iterator->next) {
		if (g_slist_find_custom (list_user_theme, iterator->data, &awf_compare_theme)) {
			menuitem = create_menuitem_radio (menu, iterator->data, FALSE, FALSE, TRUE, group);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
			if (strcmp ((gchar*) current_theme, (gchar*) iterator->data) == 0)
				gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
			g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (update_theme), iterator->data);
		}
		else {
			menuitem = create_menuitem_radio (menu, iterator->data, FALSE, FALSE, FALSE, group);
			group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
			if (strcmp ((gchar*) current_theme, (gchar*) iterator->data) == 0)
				gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
			g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (update_theme), iterator->data);
		}
	}

	if (!list_system_theme)
		create_menuitem (menu, _app("No themes found"), TRUE, NULL, NULL, NULL);

	// user themes
	menu = create_menu (root, _app("_User themes"));
	for (iterator = list_user_theme; iterator; iterator = iterator->next) {
		menuitem = create_menuitem_radio (menu, iterator->data, FALSE, FALSE, FALSE, group);
		group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));
		if (strcmp ((gchar*) current_theme, (gchar*) iterator->data) == 0)
			gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (update_theme), iterator->data);
	}

	if (!list_user_theme)
		create_menuitem (menu, _app("No themes found"), TRUE, NULL, NULL, NULL);

	// text direction
	group = NULL;
	menu  = create_menu (root, _app("_Text direction"));

		menuitem = create_menuitem_radio (menu, _app("Left to Right (LTR)"), FALSE, FALSE, FALSE, group);
		if ((current_direction == GTK_TEXT_DIR_LTR) || (current_direction == 1))
			gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (update_text_direction), (gpointer) GTK_TEXT_DIR_LTR);
		group = gtk_radio_menu_item_get_group (GTK_RADIO_MENU_ITEM (menuitem));

		menuitem = create_menuitem_radio (menu, _app("Right to Left (RTL)"), FALSE, FALSE, FALSE, group);
		if ((current_direction == GTK_TEXT_DIR_RTL) || (current_direction == 2))
			gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), TRUE);
		g_signal_connect_swapped (menuitem, "activate", G_CALLBACK (update_text_direction), (gpointer) GTK_TEXT_DIR_RTL);

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	accels_load ();
	g_object_set (gtk_settings_get_default (), "gtk-can-change-accels", FALSE, NULL);
}

static GtkWidget* create_menu (GtkWidget *root, gchar *text) {

	GtkWidget *menu, *menuitem;

	menu = gtk_menu_new ();
	menuitem = gtk_menu_item_new_with_mnemonic (text);
	gtk_menu_item_set_submenu (GTK_MENU_ITEM (menuitem), menu);
	gtk_menu_shell_append (GTK_MENU_SHELL (root), menuitem);

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	gtk_widget_set_events (menu, GDK_KEY_RELEASE_MASK);
	g_signal_connect (menu, "key-release-event", G_CALLBACK (accels_change), NULL);

	return menu;
}

static GtkWidget* create_menuitem_tearoff (GtkWidget *menu) {

	GtkWidget *menuitem;

	#if GTK_CHECK_VERSION (3,0,0)
		menuitem = gtk_tearoff_menu_item_new ();
		gtk_style_context_add_class (gtk_widget_get_style_context (menuitem), "tearoff");
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	#else
		menuitem = gtk_tearoff_menu_item_new ();
		gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	#endif

	return menuitem;
}

static GtkWidget* create_menuitem_check (GtkWidget *menu, gchar *text, gboolean checked, gboolean inconsistent, gboolean disabled) {

	GtkWidget *menuitem;

	menuitem = gtk_check_menu_item_new_with_mnemonic (text);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), checked);
	gtk_check_menu_item_set_inconsistent (GTK_CHECK_MENU_ITEM (menuitem), inconsistent);
	gtk_widget_set_sensitive (menuitem, !disabled);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

	return menuitem;
}

static GtkWidget* create_menuitem_radio (GtkWidget *menu, gchar *text, gboolean checked, gboolean inconsistent, gboolean disabled, GSList *group) {

	GtkWidget *menuitem;

	menuitem = gtk_radio_menu_item_new_with_mnemonic (group, text);
	gtk_check_menu_item_set_inconsistent (GTK_CHECK_MENU_ITEM (menuitem), inconsistent);
	gtk_check_menu_item_set_active (GTK_CHECK_MENU_ITEM (menuitem), checked);
	gtk_widget_set_sensitive (menuitem, !disabled);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);

	return menuitem;
}

static GtkWidget* create_menuitem (GtkWidget *menu, gchar *text, gboolean disabled, gchar *accel, gchar *keymap, GCallback function) {

	GtkWidget *menuitem;
	GdkModifierType mods;
	guint key;

	menuitem = gtk_image_menu_item_new_from_stock (text, NULL);
	gtk_menu_shell_append (GTK_MENU_SHELL (menu), menuitem);
	gtk_menu_item_set_accel_path (GTK_MENU_ITEM (menuitem), keymap);
	gtk_widget_set_sensitive (menuitem, !disabled);

	if (accel) {
		gtk_accelerator_parse (accel, &key, &mods);
		gtk_accel_map_add_entry (keymap, key, mods);
	}

	if (function)
		g_signal_connect (menuitem, "activate", function, NULL);

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	g_signal_connect (menuitem, "select", G_CALLBACK (accels_select), NULL);
	g_signal_connect (menuitem, "deselect", G_CALLBACK (accels_deselect), NULL);

	return menuitem;
}

static void accels_load () {

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)

	gchar *path = g_build_filename ("/", g_getenv ("HOME"), ".awf-gtk-accels", NULL);
	if (g_file_test (path, G_FILE_TEST_IS_REGULAR))
		gtk_accel_map_load (path);
	g_free (path);
}

static void accels_select (GtkWidget *widget) {

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	current_menuitem = widget;
}

static void accels_deselect (GtkWidget *widget) {

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	if (current_menuitem == widget)
		current_menuitem = NULL;
}

static void accels_change (GtkWidget *widget, GdkEventKey *event) {

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	// https://gitlab.gnome.org/GNOME/gtk/-/commit/2d79334bb069224966b3dcd8456967c9800e8fd0
	if (!current_menuitem)
		return;

	GtkMenuItem *menuitem = GTK_MENU_ITEM (current_menuitem);
	gchar *key = gdk_keyval_name (event->keyval);

	if (
		!gtk_menu_item_get_accel_path (menuitem) ||
		(strcmp (key, "Control_L") == 0) || (strcmp (key, "Control_R") == 0) ||
		(strcmp (key, "Shift_L") == 0) || (strcmp (key, "Shift_R") == 0) ||
		(strcmp (key, "Super_L") == 0) || (strcmp (key, "Super_R") == 0) ||
		(strcmp (key, "Meta_L") == 0) || (strcmp (key, "Meta_R") == 0) ||
		(strcmp (key, "Alt_L") == 0) || (strcmp (key, "Alt_R") == 0)
	) {
		return;
	}

	if (
		(event->keyval == GDK_KEY_Delete) || (event->keyval == GDK_KEY_KP_Delete) || (event->keyval == GDK_KEY_BackSpace) ||
		// f1..12
		((event->keyval >= GDK_KEY_F1) && (event->keyval <= GDK_KEY_F12)) ||
		// crtl/shift/super/alt + ?
		(event->state & GDK_CONTROL_MASK) || (event->state & GDK_SHIFT_MASK) || (event->state & GDK_SUPER_MASK) || (event->state & GDK_META_MASK)
	) {
		must_save_accels = TRUE;
		if ((event->keyval == GDK_KEY_Delete) || (event->keyval == GDK_KEY_KP_Delete) || (event->keyval == GDK_KEY_BackSpace))
			gtk_accel_map_change_entry (gtk_menu_item_get_accel_path (menuitem), 0, 0, TRUE);
		else
			gtk_accel_map_change_entry (
				gtk_menu_item_get_accel_path (menuitem),
				gdk_keyval_to_lower (event->keyval),
				event->state & gtk_accelerator_get_default_mod_mask (),
				TRUE);
	}
}

static void accels_save () {

	// gtk-can-change-accels for GTK 3.x (3.2/3.24)
	if (must_save_accels) {
		gchar *path = g_build_filename ("/", g_getenv ("HOME"), ".awf-gtk-accels", NULL);
		gtk_accel_map_save (path);
		g_free (path);
	}
}

#endif


// dialogs

static void dialog_open () {

	#if GTK_CHECK_VERSION (4,0,0)

		GtkWidget *dialog = gtk_file_chooser_dialog_new (
			"GtkFileChooserDialog",
			GTK_WINDOW (window),
			GTK_FILE_CHOOSER_ACTION_OPEN,
			_gtk("_Cancel"),
			GTK_RESPONSE_CANCEL,
			_gtk("_Open"),
			GTK_RESPONSE_ACCEPT,
			NULL);

		gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		GtkWidget *dialog = gtk_file_chooser_dialog_new (
			"GtkFileChooserDialog",
			GTK_WINDOW (window),
			GTK_FILE_CHOOSER_ACTION_OPEN,
			"gtk-cancel",
			GTK_RESPONSE_CANCEL,
			"gtk-open",
			GTK_RESPONSE_ACCEPT,
			NULL);

		gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_recent () {

	#if !GTK_CHECK_VERSION (4,0,0)

		GtkWidget *dialog = gtk_recent_chooser_dialog_new (
			"GtkRecentChooserDialog",
			GTK_WINDOW (window),
			"gtk-cancel",
			GTK_RESPONSE_CANCEL,
			"gtk-open",
			GTK_RESPONSE_ACCEPT,
			NULL);

		gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_save () {

	#if GTK_CHECK_VERSION (4,0,0)

		GtkWidget *dialog = gtk_file_chooser_dialog_new (
			"GtkFileChooserDialog",
			GTK_WINDOW (window),
			GTK_FILE_CHOOSER_ACTION_SAVE,
			_gtk("_Cancel"),
			GTK_RESPONSE_CANCEL,
			_gtk("_Save"),
			GTK_RESPONSE_ACCEPT,
			NULL);

		gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		GtkWidget *dialog = gtk_file_chooser_dialog_new (
			"GtkFileChooserDialog",
			GTK_WINDOW (window),
			GTK_FILE_CHOOSER_ACTION_SAVE,
			"gtk-cancel",
			GTK_RESPONSE_CANCEL,
			"gtk-save",
			GTK_RESPONSE_ACCEPT,
			NULL);

		gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_message () {

	GtkWidget *dialog = gtk_message_dialog_new (
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_INFO,
		GTK_BUTTONS_YES_NO,
		"GtkMessageDialog");

	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), _app("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme."));

	gtk_window_set_title (GTK_WINDOW (dialog), "GtkMessageDialog");
	gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_page_setup () {

	GtkWidget *dialog = gtk_page_setup_unix_dialog_new ("GtkPageSetupUnixDialog", GTK_WINDOW (window));
	gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_print () {

	GtkWidget *dialog = gtk_print_unix_dialog_new ("GtkPrintUnixDialog", GTK_WINDOW (window));
	gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_about () {

	gchar *t1, *t2, *t3, *t4;

	gtk_show_about_dialog (GTK_WINDOW (window),
		"version", VERSION,
		"comments", t1 = g_strdup_printf ("%s\n\n%s\n%s\n\n%s\n%s",
			_app("A widget factory is a theme preview application for GTK. It displays the various widget types provided by GTK in a single window allowing to see the visual effect of the applied theme."),
			t2 = g_strdup_printf (_app("Remove %s file"), "~/.awf-gtk-accels"),
			_app("to reset keyboard shortcuts."),
			t3 = g_strdup_printf (_app("compiled with gtk %d.%d.%d and glib %d.%d.%d and pango %s"),
				GTK_MAJOR_VERSION, GTK_MINOR_VERSION, GTK_MICRO_VERSION,
				GLIB_MAJOR_VERSION, GLIB_MINOR_VERSION, GLIB_MICRO_VERSION,
				PANGO_VERSION_STRING),
			t4 = g_strdup_printf (_app(" started with gtk %d.%d.%d and glib %d.%d.%d and pango %s"),
				gtk_major_version, gtk_minor_version, gtk_micro_version,
				glib_major_version, glib_minor_version, glib_micro_version,
				pango_version_string ())
		),
		"website", "https://github.com/luigifab/awf-extended",
		"copyright", "Copyright © 2020-2023 Fabrice Creuzot (luigifab)\nCopyright © 2011-2017 Valère Monseur (valr)",
		"icon-name", GETTEXT_PACKAGE,
		"logo-icon-name", GETTEXT_PACKAGE,
		"license", "A widget factory is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.",
		"wrap-license", TRUE,
		NULL);

	g_free (t1);
	g_free (t2);
	g_free (t3);
	g_free (t4);
}

static void dialog_calendar () {

	GtkWidget *dialog, *infobar, *label, *calendar, *vbox = BOXV, *area;

	dialog = gtk_dialog_new_with_buttons (
		NULL,
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		NULL,
		NULL);

	gtk_widget_set_size_request (dialog, 350, -1);

	// info bars and calendar
	#if GTK_CHECK_VERSION (4,0,0)

		G_GNUC_BEGIN_IGNORE_DEPRECATIONS

		infobar = gtk_info_bar_new_with_buttons (_gtk("_OK"), GTK_RESPONSE_OK, NULL);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_INFO);
		label = gtk_label_new (_app("This is an info bar."));
		gtk_info_bar_add_child (GTK_INFO_BAR (infobar), label);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		infobar = gtk_info_bar_new_with_buttons (_app("Ok"), GTK_RESPONSE_OK, NULL);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_QUESTION);
		label = gtk_label_new (_app("This is a question bar."));
		gtk_info_bar_add_child (GTK_INFO_BAR (infobar), label);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		infobar = gtk_info_bar_new ();
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_WARNING);
		label = gtk_label_new (_app("This is a warning bar."));
		gtk_info_bar_add_child (GTK_INFO_BAR (infobar), label);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		infobar = gtk_info_bar_new ();
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_ERROR);
		label = gtk_label_new (_app("This is an error bar."));
		gtk_info_bar_add_child (GTK_INFO_BAR (infobar), label);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		calendar = gtk_calendar_new ();
		gtk_calendar_set_show_day_names (GTK_CALENDAR (calendar), TRUE);
		gtk_calendar_set_show_week_numbers (GTK_CALENDAR (calendar), TRUE);
		add_to (GTK_BOX (vbox), calendar, FALSE, FALSE, 0, 0);

		G_GNUC_END_IGNORE_DEPRECATIONS
	#else
		infobar = gtk_info_bar_new_with_buttons ("gtk-ok", GTK_RESPONSE_OK, NULL);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_INFO);
		label = gtk_label_new (_app("This is an info bar."));
		add_to (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		infobar = gtk_info_bar_new_with_buttons (_app("Ok"), GTK_RESPONSE_OK, NULL);
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_QUESTION);
		label = gtk_label_new (_app("This is a question bar."));
		add_to (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		infobar = gtk_info_bar_new ();
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_WARNING);
		label = gtk_label_new (_app("This is a warning bar."));
		add_to (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		infobar = gtk_info_bar_new ();
		gtk_info_bar_set_message_type (GTK_INFO_BAR (infobar), GTK_MESSAGE_ERROR);
		label = gtk_label_new (_app("This is an error bar."));
		add_to (GTK_BOX (infobar), label, FALSE, FALSE, 0, 0);
		add_to (GTK_BOX (vbox), infobar, FALSE, FALSE, 0, 0);

		calendar = gtk_calendar_new ();
		gtk_calendar_set_display_options (GTK_CALENDAR (calendar), GTK_CALENDAR_SHOW_HEADING |
			GTK_CALENDAR_SHOW_DAY_NAMES | GTK_CALENDAR_SHOW_WEEK_NUMBERS);
		add_to (GTK_BOX (vbox), calendar, FALSE, FALSE, 0, 0);
	#endif

	// dialog
	area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	add_to (GTK_BOX (area), vbox, TRUE, TRUE, 5, 5);

	#if GTK_CHECK_VERSION (4,0,0)
		// https://blog.gtk.org/2022/10/30/on-deprecations/
		G_GNUC_BEGIN_IGNORE_DEPRECATIONS
		gtk_dialog_add_button (GTK_DIALOG (dialog), _gtk("_Cancel"), 0);
		gtk_dialog_add_button (GTK_DIALOG (dialog), _gtk("_OK"), 0);
		G_GNUC_END_IGNORE_DEPRECATIONS
	#else
		gtk_dialog_add_button (GTK_DIALOG (dialog), "gtk-cancel", 0);
		gtk_dialog_add_button (GTK_DIALOG (dialog), "gtk-ok", 0);
		gtk_widget_show_all (dialog);
	#endif

	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_window_set_title (GTK_WINDOW (dialog), "GtkDialog");
	gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}

static void dialog_scales_top () {
	dialog_scales (GTK_POS_TOP);
}

static void dialog_scales_bottom () {
	dialog_scales (GTK_POS_BOTTOM);
}

static void dialog_scales_right () {
	dialog_scales (GTK_POS_RIGHT);
}

static void dialog_scales_left () {
	dialog_scales (GTK_POS_LEFT);
}

static void dialog_scales (int position) {

	GtkWidget *dialog, *area, *hbox = BOXH;
	GtkWidget *vbox1 = BOXV, *vbox2 = BOXV, *vbox3 = BOXV, *hboxa = BOXH, *hboxb = BOXH;
	GtkWidget *scale1v, *scale2v, *scale3v, *scale4v, *scale5v, *scale6v, *scale7v, *scale8v, *scale9v, *scale10v, *scale11v, *scale12v;
	GtkWidget *scale1h, *scale2h, *scale3h, *scale4h, *scale5h, *scale6h, *scale7h, *scale8h, *scale9h, *scale10h, *scale11h, *scale12h;
	gdouble value = gtk_range_get_value (GTK_RANGE (scale1));

	dialog = gtk_dialog_new_with_buttons (
		NULL,
		GTK_WINDOW (window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		NULL,
		NULL);

	// vertical scales
	scale1v = create_vertical_scale (value, FALSE, FALSE, position);
	#if GTK_CHECK_VERSION (4,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_widget_add_css_class (scale1v, "top");
	#elif GTK_CHECK_VERSION (3,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_style_context_add_class (gtk_widget_get_style_context (scale1v), "top");
	#endif

	scale2v = create_vertical_scale (value, FALSE, FALSE, position);
	update_marks (GTK_SCALE (scale2v), FALSE, GTK_POS_LEFT);
	#if GTK_CHECK_VERSION (4,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_widget_add_css_class (scale2v, "top");
	#elif GTK_CHECK_VERSION (3,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_style_context_add_class (gtk_widget_get_style_context (scale2v), "top");
	#endif

	scale3v = create_vertical_scale (value, FALSE, FALSE, position);
	update_marks (GTK_SCALE (scale3v), TRUE, GTK_POS_LEFT);
	#if GTK_CHECK_VERSION (4,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_widget_add_css_class (scale3v, "top");
	#elif GTK_CHECK_VERSION (3,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_style_context_add_class (gtk_widget_get_style_context (scale3v), "top");
	#endif

	scale4v = create_vertical_scale (value, TRUE, FALSE, position);
	#if GTK_CHECK_VERSION (4,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_widget_add_css_class (scale4v, "top");
	#elif GTK_CHECK_VERSION (3,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_style_context_add_class (gtk_widget_get_style_context (scale4v), "top");
	#endif

	scale5v = create_vertical_scale (value, TRUE, FALSE, position);
	update_marks (GTK_SCALE (scale5v), FALSE, GTK_POS_LEFT);
	#if GTK_CHECK_VERSION (4,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_widget_add_css_class (scale5v, "top");
	#elif GTK_CHECK_VERSION (3,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_style_context_add_class (gtk_widget_get_style_context (scale5v), "top");
	#endif

	scale6v = create_vertical_scale (value, TRUE, FALSE, position);
	update_marks (GTK_SCALE (scale6v), TRUE, GTK_POS_LEFT);
	#if GTK_CHECK_VERSION (4,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_widget_add_css_class (scale6v, "top");
	#elif GTK_CHECK_VERSION (3,0,0)
		if (gtk_widget_get_direction (window) == GTK_TEXT_DIR_RTL) // @todo highlight bottom instead of top, why?
			gtk_style_context_add_class (gtk_widget_get_style_context (scale6v), "top");
	#endif

	scale7v = create_vertical_scale (value, FALSE, TRUE, position);

	scale8v = create_vertical_scale (value, FALSE, TRUE, position);
	update_marks (GTK_SCALE (scale8v), FALSE, GTK_POS_RIGHT);

	scale9v = create_vertical_scale (value, FALSE, TRUE, position);
	update_marks (GTK_SCALE (scale9v), TRUE, GTK_POS_RIGHT);

	scale10v = create_vertical_scale (value, TRUE, TRUE, position);

	scale11v = create_vertical_scale (value, TRUE, TRUE, position);
	update_marks (GTK_SCALE (scale11v), FALSE, GTK_POS_RIGHT);

	scale12v = create_vertical_scale (value, TRUE, TRUE, position);
	update_marks (GTK_SCALE (scale12v), TRUE, GTK_POS_RIGHT);

	// horizontal scales
	scale1h = create_horizontal_scale (value, FALSE, FALSE, position);

	scale2h = create_horizontal_scale (value, FALSE, FALSE, position);
	update_marks (GTK_SCALE (scale2h), FALSE, GTK_POS_TOP);

	scale3h = create_horizontal_scale (value, FALSE, FALSE, position);
	update_marks (GTK_SCALE (scale3h), TRUE, GTK_POS_TOP);

	scale4h = create_horizontal_scale (value, TRUE, FALSE, position);

	scale5h = create_horizontal_scale (value, TRUE, FALSE, position);
	update_marks (GTK_SCALE (scale5h), FALSE, GTK_POS_TOP);

	scale6h = create_horizontal_scale (value, TRUE, FALSE, position);
	update_marks (GTK_SCALE (scale6h), TRUE, GTK_POS_TOP);

	scale7h = create_horizontal_scale (value, FALSE, TRUE, position);

	scale8h = create_horizontal_scale (value, FALSE, TRUE, position);
	update_marks (GTK_SCALE (scale8h), FALSE, GTK_POS_BOTTOM);

	scale9h = create_horizontal_scale (value, FALSE, TRUE, position);
	update_marks (GTK_SCALE (scale9h), TRUE, GTK_POS_BOTTOM);

	scale10h = create_horizontal_scale (value, TRUE, TRUE, position);

	scale11h = create_horizontal_scale (value, TRUE, TRUE, position);
	update_marks (GTK_SCALE (scale11h), FALSE, GTK_POS_BOTTOM);

	scale12h = create_horizontal_scale (value, TRUE, TRUE, position);
	update_marks (GTK_SCALE (scale12h), TRUE, GTK_POS_BOTTOM);

	// dialog
	area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	add_to (GTK_BOX (area), hbox, TRUE, TRUE, 5, 5);
		add_to (GTK_BOX (hbox), vbox1, TRUE, TRUE, 5, 5);
			add_to (GTK_BOX (vbox1), scale1h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox1), scale2h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox1), scale3h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox1), scale4h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox1), scale5h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox1), scale6h, FALSE, FALSE, 5, 5);
		add_to (GTK_BOX (hbox), vbox2, TRUE, TRUE, 5, 5);
			add_to (GTK_BOX (vbox2), hboxa, TRUE, TRUE, 0, 0);
				add_to (GTK_BOX (hboxa), scale1v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxa), scale2v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxa), scale3v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxa), scale7v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxa), scale8v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxa), scale9v, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox2), hboxb, TRUE, TRUE, 0, 0);
				add_to (GTK_BOX (hboxb), scale4v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxb), scale5v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxb), scale6v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxb), scale10v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxb), scale11v, FALSE, FALSE, 5, 5);
				add_to (GTK_BOX (hboxb), scale12v, FALSE, FALSE, 5, 5);
		add_to (GTK_BOX (hbox), vbox3, TRUE, TRUE, 5, 5);
			add_to (GTK_BOX (vbox3), scale7h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox3), scale8h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox3), scale9h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox3), scale10h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox3), scale11h, FALSE, FALSE, 5, 5);
			add_to (GTK_BOX (vbox3), scale12h, FALSE, FALSE, 5, 5);

	#if GTK_CHECK_VERSION (4,0,0)
		// https://blog.gtk.org/2022/10/30/on-deprecations/
		G_GNUC_BEGIN_IGNORE_DEPRECATIONS
		gtk_dialog_add_button (GTK_DIALOG (dialog), _gtk("_Cancel"), 0);
		gtk_dialog_add_button (GTK_DIALOG (dialog), _gtk("_OK"), 0);
		G_GNUC_END_IGNORE_DEPRECATIONS
	#else
		gtk_dialog_add_button (GTK_DIALOG (dialog), "gtk-cancel", 0);
		gtk_dialog_add_button (GTK_DIALOG (dialog), "gtk-ok", 0);
		gtk_widget_show_all (dialog);
	#endif

	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_window_set_title (GTK_WINDOW (dialog), "GtkDialog");
	gtk_window_set_icon_name (GTK_WINDOW (dialog), GETTEXT_PACKAGE);

	#if GTK_CHECK_VERSION (4,0,0)
		gtk_widget_set_visible (dialog, TRUE);
		g_signal_connect (dialog, "response", G_CALLBACK (closedialog), NULL);
	#else
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);
	#endif
}


// scroll tabs (gtk4 or gtk3)
// https://github.com/mate-desktop/mate-control-center/blob/master/capplets/common/capplet-util.c
// for on_scrolltabs source function is capplet_dialog_page_scroll_event_cb
// of mate-appearance-properties from mate-control-center, GNU GPL 2+

#if GTK_CHECK_VERSION (4,0,0)

static gboolean on_scrolltabs (GtkEventControllerScroll *event, double dx, double dy, GtkWidget *widget) {

	// gtk-scroll-tabs for GTK 4.x
	GtkWidget *child, *event_widget, *action_widget;
	GtkNotebook *notebook;

	while (!GTK_IS_NOTEBOOK (widget))
		widget = gtk_widget_get_parent (widget);

	notebook = GTK_NOTEBOOK (widget);

	child = gtk_notebook_get_nth_page (notebook, gtk_notebook_get_current_page (notebook));
	if (child == NULL)
		return FALSE;

	// ignore scroll events from the content of the page
	event_widget = gtk_event_controller_get_widget (GTK_EVENT_CONTROLLER (event));
	if (event_widget == NULL || event_widget == child || gtk_widget_is_ancestor (event_widget, child))
		return FALSE;

	// and also from the action widgets
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_START);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return FALSE;
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_END);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return FALSE;

	if ((dy > 0) || (dx > 0))
		gtk_notebook_next_page (notebook);
	else if ((dy < 0) || (dx < 0))
		gtk_notebook_prev_page (notebook);

	return TRUE;
}

#elif GTK_CHECK_VERSION (3,4,0)

static gboolean on_scrolltabs (GtkWidget *widget, GdkEventScroll *event) {

	// gtk-scroll-tabs for GTK 3.4 to 3.24
	GtkWidget *child, *event_widget, *action_widget;
	GtkNotebook *notebook;

	while (!GTK_IS_NOTEBOOK (widget)) {
		widget = gtk_widget_get_parent (widget);}

	notebook = GTK_NOTEBOOK (widget);

	child = gtk_notebook_get_nth_page (notebook, gtk_notebook_get_current_page (notebook));
	if (child == NULL)
		return FALSE;

	// ignore scroll events from the content of the page
	event_widget = gtk_get_event_widget ((GdkEvent*) event);
	if (event_widget == NULL || event_widget == child || gtk_widget_is_ancestor (event_widget, child))
		return FALSE;

	// and also from the action widgets
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_START);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return FALSE;
	action_widget = gtk_notebook_get_action_widget (notebook, GTK_PACK_END);
	if (event_widget == action_widget || (action_widget != NULL && gtk_widget_is_ancestor (event_widget, action_widget)))
		return FALSE;

	switch (event->direction) {
		case GDK_SCROLL_RIGHT:
		case GDK_SCROLL_DOWN:
			gtk_notebook_next_page (notebook);
			break;
		case GDK_SCROLL_LEFT:
		case GDK_SCROLL_UP:
			gtk_notebook_prev_page (notebook);
			break;
		case GDK_SCROLL_SMOOTH:
			switch (gtk_notebook_get_tab_pos (notebook)) {
				case GTK_POS_LEFT:
				case GTK_POS_RIGHT:
					if (event->delta_y > 0)
						gtk_notebook_next_page (notebook);
					else if (event->delta_y < 0)
						gtk_notebook_prev_page (notebook);
					break;
				case GTK_POS_TOP:
				case GTK_POS_BOTTOM:
					if (event->delta_x > 0)
						gtk_notebook_next_page (notebook);
					else if (event->delta_x < 0)
						gtk_notebook_prev_page (notebook);
					break;
			}
			break;
	}

	return TRUE;
}

#endif

