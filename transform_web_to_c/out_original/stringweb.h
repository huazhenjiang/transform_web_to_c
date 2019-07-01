extern char blank_html[];
extern char bootstrap_slider_min_css[];
extern char bootstrap_slider_min_js[];
extern char bootstrap_min_css[];
extern char bootstrap_min_js[];
extern char file_upload_html[];
extern char index_html[];
extern char jquery_bootstrap_touchspin_css[];
extern char jquery_bootstrap_touchspin_js[];
extern char jquery_min_js[];
extern char switch_css[];
typedef struct _stringweb_table_{
	char *filename;
	char *arrayname;
	unsigned long size;
	char *ptrname;
}stb;
unsigned int stringweb_table_count=44;
stb stringweb_table[] = {
	{"blank.html", "blank_html", 0, (char *)&(blank_html[0]) },
	{"bootstrap-slider.min.css", "bootstrap_slider_min_css", 7648, (char *)&(bootstrap_slider_min_css[0]) },
	{"bootstrap-slider.min.js", "bootstrap_slider_min_js", 37734, (char *)&(bootstrap_slider_min_js[0]) },
	{"bootstrap.min.css", "bootstrap_min_css", 121200, (char *)&(bootstrap_min_css[0]) },
	{"bootstrap.min.js", "bootstrap_min_js", 37045, (char *)&(bootstrap_min_js[0]) },
	{"file_upload.html", "file_upload_html", 233, (char *)&(file_upload_html[0]) },
	{"index.html", "index_html", 38055, (char *)&(index_html[0]) },
	{"jquery.bootstrap-touchspin.css", "jquery_bootstrap_touchspin_css", 527, (char *)&(jquery_bootstrap_touchspin_css[0]) },
	{"jquery.bootstrap-touchspin.js", "jquery_bootstrap_touchspin_js", 22369, (char *)&(jquery_bootstrap_touchspin_js[0]) },
	{"jquery.min.js", "jquery_min_js", 97163, (char *)&(jquery_min_js[0]) },
	{"switch.css", "switch_css", 1430, (char *)&(switch_css[0]) },
	{NULL, NULL, 0, NULL},
};
