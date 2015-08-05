<?php
/**
 * @file
 * Google Analytics Vimeo admin configurations.
 */

/**
 * Google Analytics Vimeo settings.
 */
function googleanalytics_vimeo_settings() {
  $form['googleanalytics_vimeo_tracking_options'] = array(
    '#type' => 'fieldset', 
    '#title' => t('Select Tracking'),
    '#collapsible' => FALSE, 
    '#collapsed' => FALSE,
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_progress25'] = array(
    '#type' => 'checkbox',
    '#title' => t('25% Progress'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_progress25', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_progress50'] = array(
    '#type' => 'checkbox',
    '#title' => t('50% Progress'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_progress50', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_progress75'] = array(
    '#type' => 'checkbox',
    '#title' => t('75% Progress'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_progress75', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_videoPlayed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video Played'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_videoPlayed', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_videoPaused'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video Paused'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_videoPaused', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_videoResumed'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video Resumed'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_videoResumed', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_videoSeeking'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video Seeking'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_videoSeeking', FALSE),
  );
  $form['googleanalytics_vimeo_tracking_options']['googleanalytics_vimeo_videoCompleted'] = array(
    '#type' => 'checkbox',
    '#title' => t('Video Completed'),
    '#return_value' => TRUE,
    '#default_value' => variable_get('googleanalytics_vimeo_videoCompleted', FALSE),
  );
  // Page specific visibility configurations.
  $php_access = user_access('use text format php_code');
  $visibility = variable_get('googleanalytics_vimeo_visibility_options', 0);
  $pages = variable_get('googleanalytics_vimeo_visibility_pages', GOOGLEANALYTICS_PAGES);
  $options = array();
  $title = '';
  $description = '';
  if ($visibility == 2 && !$php_access) {
    $form['googleanalytics_vimeo_visibility_options'] = array('#type' => 'value', '#value' => 1);
    $form['googleanalytics_vimeo_visibility_pages'] = array('#type' => 'value', '#value' => $pages);
  }
  else {
    $options = array(
      t('Every page except the listed pages'),
      t('The listed pages only'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
      '%blog' => 'blog',
      '%blog-wildcard' => 'blog/*',
      '%front' => '<front>',
    ));
    if (module_exists('php') && $php_access) {
      $options[] = t('Pages on which this PHP code returns <code>TRUE</code> (experts only)');
      $title = t('Pages or PHP code');
      $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    else {
      $title = t('Pages');
    }
  }
  $form['googleanalytics_vimeo_visibility_options'] = array(
    '#type' => 'radios',
    '#title' => t('Add Google Analytics Vimeo Video Tracking to specific pages'),
    '#options' => $options,
    '#default_value' => variable_get('googleanalytics_vimeo_visibility_options', 0),
  );
  $form['googleanalytics_vimeo_visibility_pages'] = array(
    '#type' => 'textarea',
    '#title' => $title,
    '#default_value' => $pages,
    '#description' => $description,
    '#wysiwyg' => FALSE,
    '#rows' => 10,
  );
  return system_settings_form($form);
}