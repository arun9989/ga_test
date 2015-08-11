<?php
/**
 * @file
 * Google Analytics Vimeo Video Tracking inc.
 */

/**
 * Pass admin config values to Drupal js.
 */
function googleanalytics_vimeo_admin_config_js() {
  drupal_add_js(array('googleanalytics_vimeo' => array('progress25' => variable_get('googleanalytics_vimeo_progress25', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('progress50' => variable_get('googleanalytics_vimeo_progress50', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('progress75' => variable_get('googleanalytics_vimeo_progress75', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('videoPlayed' => variable_get('googleanalytics_vimeo_videoPlayed', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('videoPaused' => variable_get('googleanalytics_vimeo_videoPaused', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('videoResumed' => variable_get('googleanalytics_vimeo_videoResumed', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('videoSeeking' => variable_get('googleanalytics_vimeo_videoSeeking', FALSE))), array('type' => 'setting'));
  drupal_add_js(array('googleanalytics_vimeo' => array('videoCompleted' => variable_get('googleanalytics_vimeo_videoCompleted', FALSE))), array('type' => 'setting'));
}
/**
 * Based on visibility setting this function returns TRUE/FALSE.
 */
function googleanalytics_vimeo_visibility_pages() {
  static $page_match;

  // Cache visibility result if function is called more than once.
  if (!isset($page_match)) {

    $visibility = variable_get('googleanalytics_vimeo_visibility_options', 0);
    $setting_pages = variable_get('googleanalytics_vimeo_visibility_pages', GOOGLEANALYTICS_PAGES);

    // Match path if necessary.
    if (!empty($setting_pages)) {
      // Convert path to lowercase. This allows comparison of the same path
      // with different case. Ex: /Page, /page, /PAGE.
      $pages = drupal_strtolower($setting_pages);
      if ($visibility < 2) {
        // Convert the Drupal path to lowercase.
        $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));
        // Compare the lowercase internal and lowercase path alias (if any).
        $page_match = drupal_match_path($path, $pages);
        if ($path != current_path()) {
          $page_match = $page_match || drupal_match_path($_GET['q'], $pages);
        }
        // When $visibility has a value of 0, the tracking code is displayed on
        // all pages except those listed in $pages. When set to 1, it
        // is displayed only on those pages listed in $pages.
        $page_match = !($visibility xor $page_match);
      }
      elseif (module_exists('php')) {
        $page_match = php_eval($setting_pages);
      }
      else {
        $page_match = FALSE;
      }
    }
    else {
      $page_match = TRUE;
    }

  }
  return $page_match;
}
