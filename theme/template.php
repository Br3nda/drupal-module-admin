<?php
// $Id: template.php,v 1.1 2009/06/03 06:50:54 yhahn Exp $

/**
 * Display the list of available node types for node creation.
 */
function admin_node_add_list($content) {
  $output = '';
  if ($content) {
    $output = '<ul class="node-type-list">';
    foreach ($content as $item) {
      $output .= "<li class='clear-block'>";
      $output .= '<label>'. l($item['title'], $item['href'], $item['localized_options']) .'</label>';
      $output .= '<div class="description">'. filter_xss_admin($item['description']) .'</div>';
      $output .= "</li>";
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme_admin_block_content().
 */
function admin_admin_block_content($content, $get_runstate = FALSE) {
  static $has_run = FALSE;
  if ($get_runstate) {
    return $has_run;
  }
  $has_run = TRUE;
  $output = '';
  if (!empty($content)) {
    foreach ($content as $k => $item) {
      $id = str_replace('/', '-', $item['href']);
      $class = ' path-'. $id;

      $content[$k]['title'] = "<span class='icon'></span>{$item['title']}";
      $content[$k]['localized_options']['html'] = TRUE;
      $content[$k]['localized_options']['attributes']['class'] .= $class;
    }
    $output = system_admin_compact_mode() ? '<ul class="menu">' : '<ul class="admin-list">';
    foreach ($content as $item) {
      $output .= '<li class="leaf">';
      $output .= l($item['title'], $item['href'], $item['localized_options']);
      if (!system_admin_compact_mode()) {
        $output .= "<div class='description'>{$item['description']}</div>";
      }
      $output .= '</li>';
    }
    $output .= '</ul>';
  }
  return $output;
}

/**
 * Override of theme_system_settings_form().
 * Group buttons together @ the bottom.
 */
function admin_system_settings_form($form) {
  $buttons = '<div class="buttons">'. drupal_render($form['buttons']) .'</div>';
  return drupal_render($form) . $buttons;
}

/**
 * Override of theme_node_form().
 */
function admin_node_form($form) {
  $buttons = '<div class="buttons">'. drupal_render($form['buttons']) .'</div>';
  $sidebar = drupal_render($form['taxonomy']);
  $main = drupal_render($form);
  return "<div class='node-form clear-block'>
    <div class='right'>{$buttons}{$sidebar}</div>
    <div class='left'><div class='main'>{$main}{$buttons}</div></div>
  </div>";
}

/**
 * Override of theme_fieldset().
 */
function admin_fieldset(&$element) {
  $attr = isset($element['#attributes']) ? $element['#attributes'] : array();
  $attr['class'] = !empty($attr['class']) ? $attr['class'] : '';
  $attr['class'] .= ' fieldset';
  $attr['class'] .= !empty($element['#collapsible']) || !empty($element['#collapsed']) ? ' collapsible' : '';
  $attr['class'] .= !empty($element['#collapsed']) ? ' collapsed' : '';
  $attr = drupal_attributes($attr);

  $description = !empty($element['#description']) ? "<div class='description'>{$element['#description']}</div>" : '';
  $children = !empty($element['#children']) ? $element['#children'] : '';
  $value = !empty($element['#value']) ? $element['#value'] : '';
  $content = $description . $children . $value;

  $title = !empty($element['#title']) ? $element['#title'] : '';
  if (!empty($element['#collapsible']) || !empty($element['#collapsed'])) {
    $title = l($title, $_GET['q'], array('fragment' => 'fieldset'));
  }

  $output = "<div $attr>";
  $output .= $title ? "<h2 class='fieldset-title'>$title</h2>" : '';
  $output .= "<div class='fieldset-content clear-block'>$content</div>";
  $output .= "</div>";
  return $output;
}

/**
 * Theme function for manage options on admin/content/node, admin/user/user.
 */
function admin_admin_manage_options($form) {
  $output = "<div class='clear-block admin-options'>";
  $output .= "<label>{$form['#title']}</label>";
  foreach (element_children($form) as $id) {
    $output .= drupal_render($form[$id]);
  }
  $output .= "</div>";
  return $output;
}
