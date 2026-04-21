import {
  SocialPlatform,
  _SocialPlatformUser,
  SocialPlatformPost,
  _SocialPlatformSettings,
  SocialPlatformTheme,
  SocialPlatformPostStatus
} from "./expected";


// Valid: minimal required fields
const minimal: SocialPlatform = {
  user: {
    id: "550e8400-e29b-41d4-a716-446655440000",
    username: "john_doe",
    email: "john@example.com"
  },
  posts: [],
  settings: {}
};

// Valid: user with profile
const userWithProfile: _SocialPlatformUser = {
  id: "550e8400-e29b-41d4-a716-446655440001",
  username: "jane_doe",
  email: "jane@example.com",
  profile: {
    bio: "Software developer",
    avatar: "https://example.com/avatar.png",
    location: "San Francisco"
  }
};

// Valid: profile with null values (anyOf [string, null])
const userWithNullProfile: _SocialPlatformUser = {
  id: "550e8400-e29b-41d4-a716-446655440002",
  username: "bob",
  email: "bob@example.com",
  profile: {
    bio: null,
    location: null
  }
};

// Valid: post with all fields
const validPost: SocialPlatformPost = {
  id: "550e8400-e29b-41d4-a716-446655440003",
  title: "Hello World",
  content: "This is my first post",
  author: {
    id: "550e8400-e29b-41d4-a716-446655440001",
    username: "jane",
    email: "jane@example.com"
  },
  tags: [
    { name: "tech" },
    { name: "programming", slug: "programming" }
  ],
  status: "published"
};

// Valid: Theme enum values
const lightTheme: SocialPlatformTheme = "light";
const darkTheme: SocialPlatformTheme = "dark";
const systemTheme: SocialPlatformTheme = "system";

// Invalid: Theme must be from enum
// @ts-expect-error - theme must be light|dark|system
const invalidTheme: SocialPlatformTheme = "blue";

// Valid: PostStatus enum values
const draftStatus: SocialPlatformPostStatus = "draft";
const publishedStatus: SocialPlatformPostStatus = "published";
const archivedStatus: SocialPlatformPostStatus = "archived";

// Invalid: PostStatus must be from enum
// @ts-expect-error - status must be draft|published|archived
const invalidStatus: SocialPlatformPostStatus = "deleted";

// Valid: settings with all fields
const fullSettings: _SocialPlatformSettings = {
  theme: "dark",
  notifications: {
    email: true,
    push: false,
    sms: false
  },
  privacy: {
    profileVisible: true,
    showEmail: false
  }
};

// Valid: pinnedPost as Post
const withPinnedPost: SocialPlatform = {
  user: { id: "uuid-1", username: "test", email: "test@test.com" },
  posts: [],
  settings: {},
  pinnedPost: {
    id: "post-uuid",
    title: "Pinned Post",
    author: { id: "uuid-1", username: "test", email: "test@test.com" }
  }
};

// Valid: pinnedPost as null
const withNullPinnedPost: SocialPlatform = {
  user: { id: "uuid-1", username: "test", email: "test@test.com" },
  posts: [],
  settings: {},
  pinnedPost: null
};

// Invalid: missing required user
// @ts-expect-error - user is required
const missingUser: SocialPlatform = {
  posts: [],
  settings: {}
};

// Invalid: missing required posts
// @ts-expect-error - posts is required
const missingPosts: SocialPlatform = {
  user: { id: "uuid", username: "test", email: "test@test.com" },
  settings: {}
};

// Invalid: User missing required id
const invalidUserMissingId: SocialPlatform = {
  // @ts-expect-error - id is required
  user: { username: "test", email: "test@test.com" },
  posts: [],
  settings: {}
};

// Invalid: User missing required email
const invalidUserMissingEmail: SocialPlatform = {
  // @ts-expect-error - email is required
  user: { id: "uuid", username: "test" },
  posts: [],
  settings: {}
};

// Invalid: Post missing required title
// @ts-expect-error - title is required
const invalidPost: SocialPlatformPost = {
  id: "post-id",
  author: { id: "uuid", username: "test", email: "test@test.com" }
};

// Invalid: Post with invalid status enum
const invalidPostStatus: SocialPlatformPost = {
  id: "post-id",
  title: "Test",
  author: { id: "uuid", username: "test", email: "test@test.com" },
  // @ts-expect-error - status must be draft|published|archived
  status: "hidden"
};

// Invalid: extra property on User (additionalProperties: false)
const userExtraProperty: _SocialPlatformUser = {
  id: "uuid",
  username: "test",
  email: "test@test.com",
  // @ts-expect-error - extra property not allowed
  nickname: "testy"
};

// Valid: full example
const fullExample: SocialPlatform = {
  user: {
    id: "550e8400-e29b-41d4-a716-446655440000",
    username: "alice_dev",
    email: "alice@example.com",
    profile: {
      bio: "Full-stack developer",
      avatar: "https://example.com/alice.jpg",
      location: "New York"
    }
  },
  posts: [
    {
      id: "550e8400-e29b-41d4-a716-446655440010",
      title: "Getting Started with TypeScript",
      content: "TypeScript is great...",
      author: {
        id: "550e8400-e29b-41d4-a716-446655440000",
        username: "alice_dev",
        email: "alice@example.com"
      },
      tags: [
        { name: "typescript", slug: "typescript" },
        { name: "tutorial" }
      ],
      status: "published"
    },
    {
      id: "550e8400-e29b-41d4-a716-446655440011",
      title: "Draft: Advanced Patterns",
      author: {
        id: "550e8400-e29b-41d4-a716-446655440000",
        username: "alice_dev",
        email: "alice@example.com"
      },
      status: "draft"
    }
  ],
  settings: {
    theme: "dark",
    notifications: { email: true, push: true, sms: false },
    privacy: { profileVisible: true, showEmail: false }
  },
  followers: [
    { id: "follower-1", username: "bob", email: "bob@example.com" },
    { id: "follower-2", username: "charlie", email: "charlie@example.com", profile: { bio: null } }
  ],
  pinnedPost: {
    id: "550e8400-e29b-41d4-a716-446655440010",
    title: "Getting Started with TypeScript",
    author: { id: "550e8400-e29b-41d4-a716-446655440000", username: "alice_dev", email: "alice@example.com" }
  }
};
