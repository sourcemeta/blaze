export type SocialPlatformUser = _SocialPlatformUser;

export type SocialPlatformSettings = _SocialPlatformSettings;

export type SocialPlatformPostsItems = SocialPlatformPost;

export type SocialPlatformPosts = SocialPlatformPostsItems[];

export type SocialPlatformPinnedPost_1 = null;

export type SocialPlatformPinnedPost_0 = SocialPlatformPost;

export type SocialPlatformPinnedPost =
  SocialPlatformPinnedPost_0 |
  SocialPlatformPinnedPost_1;

export type SocialPlatformFollowersItems = _SocialPlatformUser;

export type SocialPlatformFollowers = SocialPlatformFollowersItems[];

export type SocialPlatformAdditionalProperties = never;

export type SocialPlatformUserUsername = string;

export type SocialPlatformUserProfile = SocialPlatformProfile;

export type SocialPlatformUserId = SocialPlatformUUID;

export type SocialPlatformUserEmail = SocialPlatformEmail;

export type SocialPlatformUserAdditionalProperties = never;

export interface _SocialPlatformUser {
  "id": SocialPlatformUserId;
  "username": SocialPlatformUserUsername;
  "email": SocialPlatformUserEmail;
  "profile"?: SocialPlatformUserProfile;
}

export type SocialPlatformUUID = string;

export type SocialPlatformURL = string;

export type SocialPlatformTheme = "light" | "dark" | "system";

export type SocialPlatformTagSlug = string;

export type SocialPlatformTagName = string;

export type SocialPlatformTagAdditionalProperties = never;

export interface SocialPlatformTag {
  "name": SocialPlatformTagName;
  "slug"?: SocialPlatformTagSlug;
}

export type SocialPlatformSettingsTheme = SocialPlatformTheme;

export type SocialPlatformSettingsPrivacy = SocialPlatformPrivacySettings;

export type SocialPlatformSettingsNotifications = SocialPlatformNotificationSettings;

export type SocialPlatformSettingsAdditionalProperties = never;

export interface _SocialPlatformSettings {
  "theme"?: SocialPlatformSettingsTheme;
  "notifications"?: SocialPlatformSettingsNotifications;
  "privacy"?: SocialPlatformSettingsPrivacy;
}

export type SocialPlatformProfileLocation_1 = null;

export type SocialPlatformProfileLocation_0 = string;

export type SocialPlatformProfileLocation =
  SocialPlatformProfileLocation_0 |
  SocialPlatformProfileLocation_1;

export type SocialPlatformProfileBio_1 = null;

export type SocialPlatformProfileBio_0 = string;

export type SocialPlatformProfileBio =
  SocialPlatformProfileBio_0 |
  SocialPlatformProfileBio_1;

export type SocialPlatformProfileAvatar = SocialPlatformURL;

export type SocialPlatformProfileAdditionalProperties = never;

export interface SocialPlatformProfile {
  "bio"?: SocialPlatformProfileBio;
  "avatar"?: SocialPlatformProfileAvatar;
  "location"?: SocialPlatformProfileLocation;
}

export type SocialPlatformPrivacySettingsShowEmail = boolean;

export type SocialPlatformPrivacySettingsProfileVisible = boolean;

export type SocialPlatformPrivacySettingsAdditionalProperties = never;

export interface SocialPlatformPrivacySettings {
  "profileVisible"?: SocialPlatformPrivacySettingsProfileVisible;
  "showEmail"?: SocialPlatformPrivacySettingsShowEmail;
}

export type SocialPlatformPostStatus = "draft" | "published" | "archived";

export type SocialPlatformPostTitle = string;

export type SocialPlatformPostTagsItems = SocialPlatformTag;

export type SocialPlatformPostTags = SocialPlatformPostTagsItems[];

export type _SocialPlatformPostStatus = SocialPlatformPostStatus;

export type SocialPlatformPostId = SocialPlatformUUID;

export type SocialPlatformPostContent = string;

export type SocialPlatformPostAuthor = _SocialPlatformUser;

export type SocialPlatformPostAdditionalProperties = never;

export interface SocialPlatformPost {
  "id": SocialPlatformPostId;
  "title": SocialPlatformPostTitle;
  "content"?: SocialPlatformPostContent;
  "author": SocialPlatformPostAuthor;
  "tags"?: SocialPlatformPostTags;
  "status"?: _SocialPlatformPostStatus;
}

export type SocialPlatformNotificationSettingsSms = boolean;

export type SocialPlatformNotificationSettingsPush = boolean;

export type SocialPlatformNotificationSettingsEmail = boolean;

export type SocialPlatformNotificationSettingsAdditionalProperties = never;

export interface SocialPlatformNotificationSettings {
  "email"?: SocialPlatformNotificationSettingsEmail;
  "push"?: SocialPlatformNotificationSettingsPush;
  "sms"?: SocialPlatformNotificationSettingsSms;
}

export type SocialPlatformEmail = string;

export interface SocialPlatform {
  "user": SocialPlatformUser;
  "posts": SocialPlatformPosts;
  "settings": SocialPlatformSettings;
  "followers"?: SocialPlatformFollowers;
  "pinnedPost"?: SocialPlatformPinnedPost;
}
