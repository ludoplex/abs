Revert the following commit, it makes the freebsd doc chain fail.

From 8eb55d782a2b9afacc7938694891cc6fad7b42a5 Mon Sep 17 00:00:00 2001
From: Dennis Filder <d.filder@web.de>
Date: Fri, 13 Jun 2014 14:56:14 +0800
Subject: xmlSaveUri() incorrectly recomposes URIs with rootless paths

For https://bugzilla.gnome.org/show_bug.cgi?id=731063

xmlSaveUri() of libxml2 (snapshot 2014-05-31 and earlier) returns
bogus values when called with URIs that have rootless paths
(e.g. "urx:b:b" becomes "urx://b%3Ab" where "urx:b%3Ab" would be
correct)

--- uri.c.orig	2014-10-03 13:28:06.000000000 +0200
+++ uri.c	2014-10-20 14:22:57.677231158 +0200
@@ -1198,6 +1198,8 @@
                 if (temp == NULL) goto mem_error;
                 ret = temp;
 	    }
+	    ret[len++] = '/';
+	    ret[len++] = '/';
 	}
 	if (uri->path != NULL) {
 	    p = uri->path;
