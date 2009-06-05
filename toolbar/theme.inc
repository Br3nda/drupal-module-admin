<?php

/**
 * Preprocessor for theme('admin_toolbar').
 */
function admin_preprocess_admin_toolbar(&$vars) {
  // Gather active paths -- we will check individual toolbars against
  // these to see if any are active.
  $active_paths = array();
  $trail = menu_get_active_trail();
  foreach ($trail as $item) {
    if (!empty($item['href'])) {
      $active_paths[] = $item['href'];
    }
  }

  $vars['collapsed'] = TRUE;

  foreach ($vars['tree'] as $depth => $menus) {
    foreach ($menus as $href => $links) {
      $class = ($depth > 0) ? 'collapsed' : '';
      if ($depth > 0 && in_array($href, $active_paths)) {
        $class = '';
        $vars['collapsed'] = FALSE;
      }
      $id = str_replace('/', '-', $href);
      $vars["tree_{$depth}"][$id] = theme('links', $links, array('class' => "links clear-block $class", 'id' => "admin-toolbar-{$id}"));
    }
  }
}

/**
 * Theme function for contextual popups.
 */
function admin_preprocess_admin_links(&$vars) {
  $links = '';
  if (!empty($vars['links'])) {
    foreach ($vars['links'] as $link) {
      $links .= l($link['title'], $link['href'], $link);
    }
  }
  $vars['links'] = $links;
}
