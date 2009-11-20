<?php
// $Id: admin.admin.inc,v 1.1.2.3.2.1 2009/11/20 02:44:31 yhahn Exp $

/**
 * System settings form for admin toolbar.
 */
function admin_settings_form() {  
  $form['admin_toolbar'] = array('#tree' => TRUE);
  $form['admin_toolbar']['layout'] = array(
    '#type' => 'select',
    '#title' => t('Layout'),
    '#description' => t('Choose a layout for the admin toolbar. Vertical works well with large, wide screens. Horizontal works well on screens with limited real estate.'),
    '#options' => array(
      'horizontal' => t('Horizontal'),
      'vertical' => t('Vertical'),
    ),
    '#default_value' => admin_get_settings('layout'),
  );
  $form['admin_toolbar']['position'] = array(
    '#type' => 'select',
    '#title' => t('Position'),
    '#description' => t('Choose a position for the admin toolbar that will not collide with other elements in your current theme.'),
    '#options' => array(
      'ne' => t('Top right'),
      'nw' => t('Top left'),
      'se' => t('Bottom right'),
      'sw' => t('Bottom left'),
    ),
    '#default_value' => admin_get_settings('position'),
  );

  // Get options.
  $options = array();
  foreach (admin_get_default_blocks() as $bid) {
    list($module, $delta) = explode('-', $bid, 2);
    $info = module_invoke($module, 'block', 'list');
    if (isset($info[$delta]['info'])) {
      $options[$bid] = $info[$delta]['info'];
    }
  }
  $form['admin_toolbar']['blocks'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Enabled blocks'),
    '#description' => t('Choose blocks to enable in the admin toolbar.'),
    '#options' => $options,
    '#default_value' => admin_get_settings('blocks'),
  );
  return system_settings_form($form);
}
