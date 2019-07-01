/*
typedef struct _web_res
{
 	const char* name;
 	unsigned long len;
 	unsigned char* ptr;
}web_res,*Pweb_res;

static const web_res resources[] = 
{
 {"index_html",sizeof(index_html),(unsigned char*)&index_html[0]},
 
 {NULL,0,NULL,};
}
*/

unsigned int stringweb_table_count=44;
const char *stringweb_table[] = {
	"blank.html", "blank_html", "0", "blank_html_ptr",
	"bootstrap-slider.min.css", "bootstrap_slider_min_css", "7648", "bootstrap_slider_min_css_ptr",
	"bootstrap-slider.min.js", "bootstrap_slider_min_js", "37734", "bootstrap_slider_min_js_ptr",
	"bootstrap.min.css", "bootstrap_min_css", "121200", "bootstrap_min_css_ptr",
	"bootstrap.min.js", "bootstrap_min_js", "37045", "bootstrap_min_js_ptr",
	"file_upload.html", "file_upload_html", "233", "file_upload_html_ptr",
	"index.html", "index_html", "38055", "index_html_ptr",
	"jquery.bootstrap-touchspin.css", "jquery_bootstrap_touchspin_css", "527", "jquery_bootstrap_touchspin_css_ptr",
	"jquery.bootstrap-touchspin.js", "jquery_bootstrap_touchspin_js", "22369", "jquery_bootstrap_touchspin_js_ptr",
	"jquery.min.js", "jquery_min_js", "97163", "jquery_min_js_ptr",
	"switch.css", "switch_css", "1430", "switch_css_ptr",
};
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
extern char *blank_html_ptr;
extern char *bootstrap_slider_min_css_ptr;
extern char *bootstrap_slider_min_js_ptr;
extern char *bootstrap_min_css_ptr;
extern char *bootstrap_min_js_ptr;
extern char *file_upload_html_ptr;
extern char *index_html_ptr;
extern char *jquery_bootstrap_touchspin_css_ptr;
extern char *jquery_bootstrap_touchspin_js_ptr;
extern char *jquery_min_js_ptr;
extern char *switch_css_ptr;


