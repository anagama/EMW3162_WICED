#include "wiced.h"
#include "http_server.h"
#include "resources.h"
#include "dns_redirect.h"
//#include "wifi_config_dct.h"
//#include "AudioCodec.h"

class start {
private:
		wiced_ip_setting_t ap_ip_settings;
		wiced_http_server_t ap_http_server;
		dns_redirector_t    dns_redirector;

public:


	/*START_OF_HTTP_PAGE_DATABASE(ap_web_pages)
			ROOT_HTTP_PAGE_REDIRECT("/index.html"),
			{ "/index.html", "text/html", WICED_RESOURCE_URL_CONTENT,   .url_content.resource_data  = &build_resources_index_html_c,    },
			{ "/test.png",   "image/png", WICED_RESOURCE_URL_CONTENT,   .url_content.resource_data  = &build_resources_test_png_c,      },
		END_OF_HTTP_PAGE_DATABASE();
		*/

	start() {
		WPRINT_PLATFORM_INFO( ("Creating class\n") );
	}
	void go(){
		WPRINT_PLATFORM_INFO( ("go\n") );
		INITIALISER_IPV4_ADDRESS( ap_ip_settings.ip_address, MAKE_IPV4_ADDRESS( 192,168,  0,  1 ) );
		INITIALISER_IPV4_ADDRESS( ap_ip_settings.netmask,    MAKE_IPV4_ADDRESS( 255,255,255,  0 ) );
		INITIALISER_IPV4_ADDRESS( ap_ip_settings.gateway,    MAKE_IPV4_ADDRESS( 192,168,  0,  1 ) );

		/* Initialise the device */
	    wiced_init();

	    /* Bring up the softAP interface ------------------------------------------------------------- */
	    wiced_network_up(WICED_AP_INTERFACE, WICED_USE_INTERNAL_DHCP_SERVER, &ap_ip_settings);

	    /* Start a DNS redirect server to redirect wiced.com to the AP webserver database*/
	    wiced_dns_redirector_start( &dns_redirector, WICED_AP_INTERFACE );
	    WPRINT_PLATFORM_INFO( ("DNS Redirector initialised\n") );
//
//	    /* Start a web server on the AP interface */
//	    wiced_http_server_start( &ap_http_server, 80, ap_web_pages, WICED_AP_INTERFACE );
//	    WPRINT_PLATFORM_INFO( ("HTTP Daemon started\n") );
	}


};

/******************************************************
 *               Function Definitions
 ******************************************************/
I2C_TypeDef i2cbus;
extern "C" {
	void application_start(void);
}

void application_start(void)
{
	WPRINT_PLATFORM_INFO( ("Starting up\n") );
	start t;
	t.go();

	//wiced_result_t result = wm8533_init(&ac);
}

