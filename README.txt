DESCRIPTION
===========

The admin module provides UI improvements to the standard Drupal admin
interface. It implements some of the ideas being explored for
usability improvements in Drupal 7.


INSTALLATION
============

1. Install & enable the module.

2. If you do not have an admin theme selected, admin will provide its
   admin theme as the default.

3. To make use of the admin header within your theme, you must add the
   following line to your theme's page.tpl.php file immediately
   following the <body> tag:

   <?php if (!empty($admin)) print $admin; ?>

4. Admin makes 2 different permissions available:

   'admin inline': Grant users access to inline contextual links for
     editing nodes, views, blocks, etc.

   'admin menu': Grant users access to the admin header/menu.


GRAPHICS
========

The icons used by the admin module were designed by Young Hahn and
AJ Ashton specifically for use with Drupal's admin interface.
The iconset is available for use under a dual GPL/BSD license,
meaning you may choose the license which is most appropriate for
your project.


API
===

There is a small API included in admin for adding contextual popup
links to various Drupal objects.

You can currently add an admin link to a block, node or view at any
time during page generation BEFORE the respective item is themed.

To add a link you can use the admin_links_set() function. You need
to specify the $type, $id, and $link parameters. Here are some
examples.

Example 1: from within hook_block():

if (module_exists('admin')) {
  $link = l(t('Configure me'), 'path/to/my/settings/page');
  admin_links_set('block', 'mymodule-delta', $link);
}

Example 2: from within hook_views_pre_view():

if (module_exists('admin')) {
  $link = admin_admin_link('views', array('view' => $view->name));
  admin_links_set('views', $view->name .'-'. $display_id, $link);
}

In this case, we use the helper function admin_admin_link(). It is
just that -- a helper function for generating some common admin links.
It also does some nice things like add &destination=$_GET['q'] to the
query string to send the user back to the current page after they
finish editing a view.


CONTRIBUTORS
============
Young Hahn young@developmentseed.org
AJ Ashton aj@developmentseed.org
