#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <gst/gst.h>
#include <errno.h>

/* 
 * código original: 
 *
 *  gst_parse_launch ( 
 * ("playbin uri=https://gstreamer.freedesktop.org/data/media/sintel_trailer-480p.webm", NULL);
 *
 * También es posible usar una archivo local
 *  "playbin uri=file:///path/to/file/demo.mp4",
 *
 * Modificación:
 *  - Requiere: 
 *  export SRC=/path/to/file/demo.mp4 
 *
 * char filePath[200] = "playbin uri=file://";
 * char *SRC = getenv("SRC"); 
 * strcat(filePath, SRC);
 * 
 * pipeline = gst_parse_launch (filePath, NULL);
 */


int tutorial_main(int argc, char *argv[]);

int 
tutorial_main(int argc, char *argv[])
{

   char filePath[200] = "playbin uri=file://";
   char *SRC = getenv("SRC"); 

   if(SRC != NULL) {
     strcat(filePath, SRC); // todo: usar strncat
   } else {
      //perror("Error "); 
     fprintf(stderr, "error getenv SRC\n");	    
   } 
   GstElement *pipeline;
   GstBus *bus;
   GstMessage *msg;

   /* Initialize GStreamer */
   gst_init (&argc, &argv);

   /* Build the pipeline */
   pipeline = gst_parse_launch (filePath, NULL);


   /* start playing */
   gst_element_set_state(pipeline, GST_STATE_PLAYING);

   /* Wait until error or EOS */
   bus = gst_element_get_bus (pipeline);
   msg = 
	gst_bus_timed_pop_filtered(bus,GST_CLOCK_TIME_NONE,
        GST_MESSAGE_ERROR | GST_MESSAGE_EOS);
  /* see next tutorial for proper error message handling/parsing */
  if(GST_MESSAGE_TYPE(msg) == GST_MESSAGE_ERROR) {
     g_printerr("An error - Re-run with GST_DEBUG=*:WARN "
		"environment variable set for more details.\n");
  }
  /* free resources */
  gst_message_unref(msg);
  gst_object_unref(bus);
  gst_element_set_state(pipeline, GST_STATE_NULL);
  gst_object_unref(pipeline);
  return 0;
}

int 
main (int argc, char *argv[])
{
return tutorial_main(argc, argv);
}


