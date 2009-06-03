<?php

/**
 * Initialize the admin "theme".
 */
function _admin_init_theme() {
  global $theme, $theme_key;
  if (empty($theme)) {
    _admin_theme_rebuild();

    $theme = $theme_key = 'admin';

    $path = drupal_get_path('module', 'admin') .'/theme';

    $theme_info = new StdClass();
    $theme_info->name = 'admin';
    $theme_info->filename = "{$path}/admin.theme.info";
    $theme_info->engine = 'phptemplate';
    $theme_info->owner = drupal_get_path('theme_engine', 'phptemplate') .'/phptemplate.engine';

    $theme_info->stylesheets = array();
    $theme_info->stylesheets['screen'][] = "{$path}/reset.css";
    $theme_info->stylesheets['screen'][] = "{$path}/style.css";

    $theme_info->scripts = array();
    $theme_info->scripts[] = "{$path}/theme.js";

    _init_theme($theme_info);
    return TRUE;
  }
}

/**
 * Generate the 1st level of navigation links under 'admin'.
 */
function admin_navigation_primary() {
  $tree = menu_tree_page_data();
  foreach ($tree as $item) {
    if ($item['link']['link_path'] == 'admin' && !empty($item['below'])) {
      return admin_menu_navigation_links($item['below']);
      break;
    }
  }
  return NULL;
}

/**
 * Generate the 2nd level of navigation links under 'admin/*'.
 */
function admin_navigation_secondary() {
  $is_duplicated = theme('admin_block_content', NULL, TRUE);
  if (!$is_duplicated) {
    $tree = menu_tree_page_data();
    foreach ($tree as $item) {
      if ($item['link']['link_path'] == 'admin' && !empty($item['below'])) {
        foreach ($item['below'] as $child) {
          if (!empty($child['link']['in_active_trail']) && !empty($child['below'])) {
            return admin_menu_navigation_links($child['below']);
          }
        }
        break;
      }
    }
  }
  return NULL;
}
